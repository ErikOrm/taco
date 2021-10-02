#include "taco/index_notation/distribution.h"
#include "taco/index_notation/index_notation.h"

namespace taco {

struct Transfer::Content {
  Content(Access a) : access(a) {}
  Access access;
};

Transfer::Transfer(taco::Access a) : content(new Content(a)) {}

Access Transfer::getAccess() const {
  return this->content->access;
}

bool operator==(Transfer& a, Transfer& b) {
  return a.content->access.getTensorVar() == b.content->access.getTensorVar();
}

std::ostream& operator<<(std::ostream& o, const Transfer& t) {
  o << "transfer(" << t.getAccess() << ")";
  return o;
}

bool transfersHaveTensorVar(const Transfers& t, TensorVar& v) {
  for (auto tx : t) {
    if (tx.getAccess().getTensorVar() == v) {
      return true;
    }
  }
  return false;
}

GridPlacement::AxisMatch Face(int face) {
  return GridPlacement::AxisMatch::makeFace(face);
}

GridPlacement::AxisMatch Replicate() {
  return GridPlacement::AxisMatch::makeReplicated();
}


PlacementGrid::Axis operator|(ir::Expr e, GridPlacement::AxisMatch axis) {
  return PlacementGrid::Axis(e, axis);
}

}