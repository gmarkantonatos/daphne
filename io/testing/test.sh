#!/bin/bash

python3 write_test_tdms_frame.py
python3 write_test_tdms_matrix.py

echo "


                         ____________________
                        |\____________________\ 
                        ||                    | 
                        ||    Matrix First    |  
                        \|____________________| 


"
../../bin/daphne readMatrix.daphne

echo " 


     
                            |_|_|_|_|_|_|_|_|_|
                            |_|_|F|R|A|M|E|_|_|
                            |_|S|E|C|O|N|D|_|_|
                            | | | | | | | | | |



"
../../bin/daphne readFrame.daphne

touch new.tdms new.tdms.meta

../../bin/daphne writeFrame.daphne

../../bin/daphne readwrittenFrame.daphne