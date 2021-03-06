#include "test.h"

#include "baldr/graphid.h"
#include "midgard/point2.h"

using namespace std;
using namespace valhalla::baldr;

namespace {

void TestCtorDefault() {
  GraphId target;
  if (target.Is_Valid())
    throw runtime_error("CtorDefault test failed, should be invalid id");
}

void TryCtorUintUintUint(const unsigned int tileid, const unsigned int level,
                         const unsigned int id, const GraphId& expected) {
  GraphId result(tileid, level, id);
  if (!(expected == result))
    throw runtime_error("CtorUintUintUint test failed");
}

void TestCtorUintUintUint() {
  TryCtorUintUintUint(10, 2, 1, GraphId(10, 2, 1));
  TryCtorUintUintUint(5, 1, 50, GraphId(5, 1, 50));
}

void TryCtorCopy(const GraphId& gid, const GraphId& expected) {
  GraphId result(gid);
  if (!(expected == result))
    throw runtime_error("CtorCopy test failed");
}

void TestCtorCopy() {
  TryCtorCopy(GraphId(10, 2, 1), GraphId(10, 2, 1));
  TryCtorCopy(GraphId(5, 1, 50), GraphId(5, 1, 50));
}

void TryGet_tileid(const GraphId& gid, const unsigned int expected) {
  if (expected != gid.tileid())
    throw runtime_error("Get_tileid test failed");
}

void TestGet_tileid() {
  TryGet_tileid(GraphId(10, 2, 1), 10);
  TryGet_tileid(GraphId(5, 1, 50), 5);
}

void TryGet_level(const GraphId& gid, const unsigned int expected) {
  if (expected != gid.level())
    throw runtime_error("Get_level test failed");
}

void TestGet_level() {
  TryGet_level(GraphId(10, 2, 1), 2);
  TryGet_level(GraphId(5, 1, 50), 1);
}

void TryGet_id(const GraphId& gid, const unsigned int expected) {
  if (expected != gid.id())
    throw runtime_error("Get_id test failed");
}

void TestGet_id() {
  TryGet_id(GraphId(10, 2, 1), 1);
  TryGet_id(GraphId(5, 1, 50), 50);
}

void TrySetUintUintUint(const unsigned int tileid, const unsigned int level,
                        const unsigned int id, const GraphId& expected) {
  GraphId result;
  result.Set(tileid, level, id);
  if (!(expected == result))
    throw runtime_error("SetUintUintUint test failed");
}

void TestSetUintUintUint() {
  TrySetUintUintUint(10, 2, 1, GraphId(10, 2, 1));
  TrySetUintUintUint(5, 1, 50, GraphId(5, 1, 50));
}

void TestIsValid() {
  GraphId id(1,2,3);
  if(!id.Is_Valid())
    throw runtime_error("Id should have been valid but was not");
  id = GraphId();
  if(id.Is_Valid())
    throw runtime_error("Default constructor should never return valid graphid");
}

void TryOpPostIncrement(GraphId& gid, const unsigned int expected) {
  auto old = gid++;
  if (expected != gid.id())
    throw runtime_error("Get_id test failed");
  if (expected - 1 != old.id())
    throw runtime_error("Get_id test failed");
}

void TestOpPostIncrement() {
  GraphId graphid1 { 10, 5, 0 };
  TryOpPostIncrement(graphid1, 1);
  GraphId graphid2 { 10, 5, 1 };
  TryOpPostIncrement(graphid2, 2);
  GraphId graphid3 { 5, 1, 50 };
  TryOpPostIncrement(graphid3, 51);
}

void TryOpLessThan(const GraphId& lhs, const GraphId& rhs) {
  if (!(lhs < rhs))
    throw runtime_error("OpLessThan test failed");
}

void TestOpLessThan() {
  TryOpLessThan(GraphId(0, 0, 0), GraphId(0, 0, 1));
  TryOpLessThan(GraphId(10, 5, 1), GraphId(10, 6, 1));
  TryOpLessThan(GraphId(5, 1, 50), GraphId(6, 1, 50));
  TryOpLessThan(GraphId(111, 6, 333), GraphId(112, 7, 334));
}

void TryOpEqualTo(const GraphId& gid, const GraphId& expected) {
  if (!(expected == gid))
    throw runtime_error("OpEqualTo test failed");
  if (!(gid == expected))
    throw runtime_error("OpEqualTo test failed");
}

void TestOpEqualTo() {
  TryOpEqualTo(GraphId(0, 0, 0), GraphId(0, 0, 0));
  TryOpEqualTo(GraphId(10, 5, 1), GraphId(10, 5, 1));
  TryOpEqualTo(GraphId(5, 1, 50), GraphId(5, 1, 50));
}

}

int main() {
  test::suite suite("graphid");

  // Ctor default
  suite.test(TEST_CASE(TestCtorDefault));

  // Ctor uint, uint, uint
  suite.test(TEST_CASE(TestCtorUintUintUint));

  // Ctor copy
  suite.test(TEST_CASE(TestCtorCopy));

  // Get tileid
  suite.test(TEST_CASE(TestGet_tileid));

  // Get level
  suite.test(TEST_CASE(TestGet_level));

  // Get id
  suite.test(TEST_CASE(TestGet_id));

  // Set uint, uint, uint
  suite.test(TEST_CASE(TestSetUintUintUint));

  // Is Valid
  suite.test(TEST_CASE(TestIsValid));

  // Op PostIncrement
  suite.test(TEST_CASE(TestOpPostIncrement));

  // Op LessThan
  suite.test(TEST_CASE(TestOpLessThan));

  // Op EqualTo
  suite.test(TEST_CASE(TestOpEqualTo));

  return suite.tear_down();
}
