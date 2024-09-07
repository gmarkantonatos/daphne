#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstring>
#include <vector>
#include <string>
#include <unordered_map>

// TOC Mask flags

#define kTocMetaData         (1L<<1)
#define kTocRawData          (1L<<3)
#define kTocDAQmxRawData     (1L<<7)
#define kTocInterleavedData  (1L<<5)
#define kTocBigEndian        (1L<<6)
#define kTocNewObjList       (1L<<2)
#define NoRawDataObj         (0xFFFFFFFF)
#define DAQmxrawdata1        (0x00001269)
#define DAQmxrawdata2        (0x00001369)

typedef enum {
    tdsTypeVoid,
    tdsTypeI8,    
    tdsTypeI16,    
    tdsTypeI32,    
    tdsTypeI64,
    tdsTypeU8,    
    tdsTypeU16,    
    tdsTypeU32,    
    tdsTypeU64,
    tdsTypeSingleFloat,    
    tdsTypeDoubleFloat,    
    tdsTypeExtendedFloat,    
    tdsTypeSingleFloatWithUnit=0x19,    
    tdsTypeDoubleFloatWithUnit,    
    tdsTypeExtendedFloatWithUnit,
    tdsTypeString=0x20,   
    tdsTypeBoolean=0x21,   
    tdsTypeTimeStamp=0x44,
    tdsTypeFixedPoint=0x4F,
    tdsTypeComplexSingleFloat=0x08000c,
    tdsTypeComplexDoubleFloat=0x10000d,
    tdsTypeDAQmxRawData=0xFFFFFFFF
} tdsDataType;

struct rawindex{
    uint32_t indexlength;
    int datatype;
    uint32_t arrdims;
    uint64_t numOfvals;
};

struct LeadIn {
    char tag[4];
    uint32_t ToCmask;
    uint32_t verionNum;
    uint64_t nextsegoff;
    uint64_t rawdataoff;
};

// Structure to manage TDMS file information
struct TdmsFile {
    std::ifstream file; // Input file stream for binary reading
    std::string filename;
};

// Structure to hold metadata for each object (group/channel)
struct ObjectMetadata {
    std::string path;
    std::unordered_map<std::string, std::string> properties;
    rawindex index;
    uint64_t totalrawlength;
    uint32_t remainingObj;
};

struct Metadata { 
    uint32_t numOfObj;
    std::unordered_map<std::string, ObjectMetadata *> objects;
};

// Function to open a TDMS file
bool openTdmsFile(TdmsFile &tdms, const std::string &filename) {
    tdms.file.open(filename, std::ios::binary);
    if (!tdms.file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return false;
    }
    tdms.filename = filename;
    return true;
}

// Function to close the TDMS file
void closeTdmsFile(TdmsFile &tdms) {
    if (tdms.file.is_open()) {
        tdms.file.close();
    }
}


// Main function to test the TDMS reader
int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <tdms_file>" << std::endl;
        return 1;
    }

    LeadIn leadin; 
    Metadata metadata;
    //char * buf ;
    TdmsFile tdms;
    if (!openTdmsFile(tdms, argv[1])) {
        return 1;
    }

    uint32_t tocMask;
    uint64_t dataOffset;

    if(!tdms.file.read((char *)&leadin , 28)){
        std::cerr << " could not read leadin\n";
        return -1 ;
    }
    char tagg[5]={0};
    memcpy(tagg,leadin.tag,4);
    tagg[4]='\0';
    std::cout << "tdms tag is :" << leadin.tag << std::endl;
    std::cout << "tdms mask is : "<< leadin.ToCmask << std::endl;
    std::cout<< " tdms version number : " << leadin.verionNum << std::endl;

    if(!(leadin.ToCmask & kTocMetaData) == 0) {
        std::cout << "segment has meta data\n";
        if(!tdms.file.read((char *)&metadata , 4)){
            std::cerr << " could not read leadin\n";
        return -1 ;
        }
        std::cout << "segment has " << metadata.numOfObj << " objects in metadata section\n";
        uint32_t pathlength;
        uint32_t rawdata;
        char * path;
        int i,j;
        for ( i=0; i<metadata.numOfObj ; i++){
            pathlength=0;
            tdms.file.read((char *)&pathlength , 4);
            path = (char *)malloc(pathlength); 
            tdms.file.read(path , pathlength);
            std::cout<< " \n\n\robject " << i << " path has lenght " << pathlength << " and the path is "<< path <<std::endl;
            
            std::string a(path,pathlength);
            //std::cout<< "created string : " << a <<std::endl;
            ObjectMetadata obj;
            //std::cout<<"before obj->path=a \n";
            obj.path=a;
            //std::cout<<"creating object\n";
            std::pair<std::string,ObjectMetadata *> met(a,&obj) ;
            free(path);
            //met = std::make_pair(obj->path,obj);
            //std::cout<<"created pair\n";
            metadata.objects.insert(met);
            //std::cout<<"inserted pair\n";
            tdms.file.read((char *)&rawdata,4);
            if(!(rawdata==NoRawDataObj)){
                obj.index.indexlength=rawdata;
                tdms.file.read(((char *)&obj.index) + 4,16);
                if(obj.index.datatype==tdsTypeString) {
                    tdms.file.read((char*)&obj.totalrawlength,8);
                }
                printf(" \n\n\r object with path %s has index: \n\r indexlength: %u \ndatatype: %u \narraydimensions: %u \nnumber of values: %lu \n\n\r",obj.path.c_str(),obj.index.indexlength,obj.index.datatype,obj.index.arrdims,obj.index.numOfvals);
            }
            else if( rawdata == DAQmxrawdata1 || rawdata == DAQmxrawdata2) 
                std::cout << "object contains DAQmx raw data really cant do shiiiit \n\n";
            else std::cout << "object doesnt contain any raw data\n";
            //else 
            //   std::cout << " object has raw data index cant do a lot \n\n";
            //if(rawdata == NoRawDataObj){
            //std::cout << "raw data index is " << rawdata << std::endl;
            uint32_t dtype;
            uint32_t value;
            double dbval;
            float flval;
            time_t timestamp;
            //__uint128_t timestamp;
            //std::cout << " no raw data obj\n";
            tdms.file.read((char *)&rawdata,4);
            std::cout << "object has "<<rawdata<<" properties\n";
            uint32_t loops=rawdata;
            for(j = 0 ; j<loops ; j++){
                tdms.file.read((char *)&pathlength , 4);
                path = (char *)malloc(pathlength); 
                tdms.file.read(path , pathlength);
                std::cout<< "object property " << j << "has lenght " << pathlength << " and the path is "<< path <<std::endl;
                tdms.file.read((char *)&dtype,4);
                std::cout<<"object property has value type : " << dtype << std::endl;  
                free(path);
                if(dtype==tdsTypeString){
                    tdms.file.read((char*) &pathlength,4);
                    path = (char *)malloc(pathlength); 
                    tdms.file.read(path , pathlength);
                    std::cout << " property has value : " <<path << " with length " << pathlength << std::endl;
                    free(path);
                }
                else if(dtype==tdsTypeTimeStamp){
                    tdms.file.read((char*)&timestamp,8);
                    tdms.file.read((char*)&timestamp,8);
                    std::cout<< " property value is the timestamp : " << ctime(&timestamp) << std::endl;
                }
                else if(dtype==tdsTypeDoubleFloat){
                    tdms.file.read((char*)&dbval,8);
                    std::cout << " property has double value : " << dbval << std::endl;
                }
                else if(dtype==tdsTypeSingleFloat){
                    tdms.file.read((char*)&flval,4);
                    std::cout << " property has float value : " << flval << std::endl;
                }
                else {
                    tdms.file.read((char *)&value,4);
                    std::cout<< " property has value : "<< value << std::endl;
                }
                //std::cout << "going to next property, j equals to "<< j << std::endl;
                
            }
                
            //} 
            
        }
        double rdat[10];
        double mean=0;
        std::cout<< "\nreading raw data , 10 double values \n";
        tdms.file.read((char*)&rdat,10*8);
        std::cout<< "[";
        for(int k=0;k<9;k++){
            std::cout<< rdat[k] <<",";
            mean+=rdat[k];
        }
        std::cout<<rdat[9]<<"]\n";
        mean+=rdat[9];
        mean/=10;
        std::cout << "the average value is : "<< mean << std::endl;
    }
    std::cout << "objects with name / exist " << metadata.objects.count("/") << "times\n";
    if((leadin.ToCmask & kTocRawData) == 0 ) std::cout << "no raw data in segment \n";
    else std::cout << "there are raw data in segment \n";

    closeTdmsFile(tdms);
    return 0;
}