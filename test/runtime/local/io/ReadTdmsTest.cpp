#include <runtime/local/datastructures/DataObjectFactory.h>
#include <runtime/local/datastructures/DenseMatrix.h>
#include <runtime/local/io/ReadTdms.h>
#include <runtime/local/io/File.h>

#include <tags.h>

#include <catch.hpp>

#include <vector>

#include <cmath>
#include <cstdint>
#include <limits>

TEMPLATE_PRODUCT_TEST_CASE("ReadTdms", TAG_IO, (DenseMatrix), (double)) {
  using DT = TestType;
  DT *m = nullptr;

  size_t numRows = 10;
  size_t numCols = 1;

  char filename[] = "./test/runtime/local/io/ReadTdms.tdms";
  char delim = ',';

  readTdms(m, filename, numRows, numCols, delim);

  REQUIRE(m->getNumRows() == numRows);
  REQUIRE(m->getNumCols() == numCols);

  CHECK(m->get(0, 0) == 1);
  CHECK(m->get(1, 0) == 2);
  CHECK(m->get(2, 0) == 3);
  CHECK(m->get(3, 0) == 4);
  CHECK(m->get(4, 0) == 5);
  CHECK(m->get(5, 0) == 6);
  CHECK(m->get(6, 0) == 7);
  CHECK(m->get(7, 0) == 8);
  CHECK(m->get(8, 0) == 9);
  CHECK(m->get(9, 0) == 10);

  DataObjectFactory::destroy(m);
}

TEST_CASE("ReadTdmsFrame1 - Floating and Integer Data Verification", TAG_IO) {
  Frame *m = NULL;
  size_t numRows = 10;
  size_t numCols = 10;
  char filename[] = "./test/runtime/local/io/readTdmsFrame1.tdms";
  ValueTypeCode schema[] = {ValueTypeCode::F64, ValueTypeCode::SI64, ValueTypeCode::F64, ValueTypeCode::SI64, ValueTypeCode::F64, ValueTypeCode::SI64, ValueTypeCode::F64, ValueTypeCode::SI64, ValueTypeCode::F64, ValueTypeCode::SI64};

  readTdms(m, filename, numRows, numCols, ',',schema);

  REQUIRE(m->getNumRows() == numRows);
  REQUIRE(m->getNumCols() == numCols);

  // Assertions to check the first few values for correctness
  CHECK(m->getColumn<double>(0)->get(0,0) == Approx(0.0));
  CHECK(m->getColumn<int64_t>(1)->get(0,0) == 0);
  CHECK(m->getColumn<double>(0)->get(9,0) == Approx(2.0));
  CHECK(m->getColumn<int64_t>(1)->get(9,0) == 9);

  DataObjectFactory::destroy(m);
}

TEST_CASE("ReadTdmsFrame2 - Integer Data Verification", TAG_IO) {
  Frame *m = NULL;
  size_t numRows = 10;
  size_t numCols = 10;
  char filename[] = "./test/runtime/local/io/readTdmsFrame2.tdms";
  ValueTypeCode schema[] = {ValueTypeCode::SI64, ValueTypeCode::SI64, ValueTypeCode::SI64, ValueTypeCode::SI64, ValueTypeCode::SI64, ValueTypeCode::SI64, ValueTypeCode::SI64, ValueTypeCode::SI64, ValueTypeCode::SI64, ValueTypeCode::SI64};

  readTdms(m, filename, numRows, numCols, ',',schema);

  REQUIRE(m->getNumRows() == numRows);
  REQUIRE(m->getNumCols() == numCols);

  // Assertions to check the values

  CHECK(m->getColumn<int64_t>(0)->get(0,0) == 10 );
  CHECK(m->getColumn<int64_t>(0)->get(9,0) == 19 );


  DataObjectFactory::destroy(m);
}
