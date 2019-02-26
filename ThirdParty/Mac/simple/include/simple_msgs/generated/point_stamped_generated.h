// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_POINTSTAMPED_SIMPLE_MSGS_H_
#define FLATBUFFERS_GENERATED_POINTSTAMPED_SIMPLE_MSGS_H_

#include "flatbuffers/flatbuffers.h"

namespace simple_msgs {

struct PointStampedFbs;

struct PointStampedFbs FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_POINT = 4,
    VT_HEADER = 6
  };
  const flatbuffers::Vector<uint8_t> *point() const {
    return GetPointer<const flatbuffers::Vector<uint8_t> *>(VT_POINT);
  }
  const flatbuffers::Vector<uint8_t> *header() const {
    return GetPointer<const flatbuffers::Vector<uint8_t> *>(VT_HEADER);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_POINT) &&
           verifier.VerifyVector(point()) &&
           VerifyOffset(verifier, VT_HEADER) &&
           verifier.VerifyVector(header()) &&
           verifier.EndTable();
  }
};

struct PointStampedFbsBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_point(flatbuffers::Offset<flatbuffers::Vector<uint8_t>> point) {
    fbb_.AddOffset(PointStampedFbs::VT_POINT, point);
  }
  void add_header(flatbuffers::Offset<flatbuffers::Vector<uint8_t>> header) {
    fbb_.AddOffset(PointStampedFbs::VT_HEADER, header);
  }
  explicit PointStampedFbsBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  PointStampedFbsBuilder &operator=(const PointStampedFbsBuilder &);
  flatbuffers::Offset<PointStampedFbs> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<PointStampedFbs>(end);
    return o;
  }
};

inline flatbuffers::Offset<PointStampedFbs> CreatePointStampedFbs(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<uint8_t>> point = 0,
    flatbuffers::Offset<flatbuffers::Vector<uint8_t>> header = 0) {
  PointStampedFbsBuilder builder_(_fbb);
  builder_.add_header(header);
  builder_.add_point(point);
  return builder_.Finish();
}

inline flatbuffers::Offset<PointStampedFbs> CreatePointStampedFbsDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<uint8_t> *point = nullptr,
    const std::vector<uint8_t> *header = nullptr) {
  return simple_msgs::CreatePointStampedFbs(
      _fbb,
      point ? _fbb.CreateVector<uint8_t>(*point) : 0,
      header ? _fbb.CreateVector<uint8_t>(*header) : 0);
}

inline const simple_msgs::PointStampedFbs *GetPointStampedFbs(const void *buf) {
  return flatbuffers::GetRoot<simple_msgs::PointStampedFbs>(buf);
}

inline const simple_msgs::PointStampedFbs *GetSizePrefixedPointStampedFbs(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<simple_msgs::PointStampedFbs>(buf);
}

inline const char *PointStampedFbsIdentifier() {
  return "PTST";
}

inline bool PointStampedFbsBufferHasIdentifier(const void *buf) {
  return flatbuffers::BufferHasIdentifier(
      buf, PointStampedFbsIdentifier());
}

inline bool VerifyPointStampedFbsBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<simple_msgs::PointStampedFbs>(PointStampedFbsIdentifier());
}

inline bool VerifySizePrefixedPointStampedFbsBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<simple_msgs::PointStampedFbs>(PointStampedFbsIdentifier());
}

inline void FinishPointStampedFbsBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<simple_msgs::PointStampedFbs> root) {
  fbb.Finish(root, PointStampedFbsIdentifier());
}

inline void FinishSizePrefixedPointStampedFbsBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<simple_msgs::PointStampedFbs> root) {
  fbb.FinishSizePrefixed(root, PointStampedFbsIdentifier());
}

}  // namespace simple_msgs

#endif  // FLATBUFFERS_GENERATED_POINTSTAMPED_SIMPLE_MSGS_H_
