// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_ROTATIONMATRIXSTAMPED_SIMPLE_MSGS_H_
#define FLATBUFFERS_GENERATED_ROTATIONMATRIXSTAMPED_SIMPLE_MSGS_H_

#include "flatbuffers/flatbuffers.h"

namespace simple_msgs {

struct RotationMatrixStampedFbs;

struct RotationMatrixStampedFbs FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_ROTATION_MATRIX = 4,
    VT_HEADER = 6
  };
  const flatbuffers::Vector<uint8_t> *rotation_matrix() const {
    return GetPointer<const flatbuffers::Vector<uint8_t> *>(VT_ROTATION_MATRIX);
  }
  const flatbuffers::Vector<uint8_t> *header() const {
    return GetPointer<const flatbuffers::Vector<uint8_t> *>(VT_HEADER);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyOffset(verifier, VT_ROTATION_MATRIX) &&
           verifier.Verify(rotation_matrix()) &&
           VerifyOffset(verifier, VT_HEADER) &&
           verifier.Verify(header()) &&
           verifier.EndTable();
  }
};

struct RotationMatrixStampedFbsBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_rotation_matrix(flatbuffers::Offset<flatbuffers::Vector<uint8_t>> rotation_matrix) {
    fbb_.AddOffset(RotationMatrixStampedFbs::VT_ROTATION_MATRIX, rotation_matrix);
  }
  void add_header(flatbuffers::Offset<flatbuffers::Vector<uint8_t>> header) {
    fbb_.AddOffset(RotationMatrixStampedFbs::VT_HEADER, header);
  }
  explicit RotationMatrixStampedFbsBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  RotationMatrixStampedFbsBuilder &operator=(const RotationMatrixStampedFbsBuilder &);
  flatbuffers::Offset<RotationMatrixStampedFbs> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<RotationMatrixStampedFbs>(end);
    return o;
  }
};

inline flatbuffers::Offset<RotationMatrixStampedFbs> CreateRotationMatrixStampedFbs(
    flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<flatbuffers::Vector<uint8_t>> rotation_matrix = 0,
    flatbuffers::Offset<flatbuffers::Vector<uint8_t>> header = 0) {
  RotationMatrixStampedFbsBuilder builder_(_fbb);
  builder_.add_header(header);
  builder_.add_rotation_matrix(rotation_matrix);
  return builder_.Finish();
}

inline flatbuffers::Offset<RotationMatrixStampedFbs> CreateRotationMatrixStampedFbsDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    const std::vector<uint8_t> *rotation_matrix = nullptr,
    const std::vector<uint8_t> *header = nullptr) {
  return simple_msgs::CreateRotationMatrixStampedFbs(
      _fbb,
      rotation_matrix ? _fbb.CreateVector<uint8_t>(*rotation_matrix) : 0,
      header ? _fbb.CreateVector<uint8_t>(*header) : 0);
}

inline const simple_msgs::RotationMatrixStampedFbs *GetRotationMatrixStampedFbs(const void *buf) {
  return flatbuffers::GetRoot<simple_msgs::RotationMatrixStampedFbs>(buf);
}

inline const simple_msgs::RotationMatrixStampedFbs *GetSizePrefixedRotationMatrixStampedFbs(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<simple_msgs::RotationMatrixStampedFbs>(buf);
}

inline const char *RotationMatrixStampedFbsIdentifier() {
  return "RMST";
}

inline bool RotationMatrixStampedFbsBufferHasIdentifier(const void *buf) {
  return flatbuffers::BufferHasIdentifier(
      buf, RotationMatrixStampedFbsIdentifier());
}

inline bool VerifyRotationMatrixStampedFbsBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<simple_msgs::RotationMatrixStampedFbs>(RotationMatrixStampedFbsIdentifier());
}

inline bool VerifySizePrefixedRotationMatrixStampedFbsBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<simple_msgs::RotationMatrixStampedFbs>(RotationMatrixStampedFbsIdentifier());
}

inline void FinishRotationMatrixStampedFbsBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<simple_msgs::RotationMatrixStampedFbs> root) {
  fbb.Finish(root, RotationMatrixStampedFbsIdentifier());
}

inline void FinishSizePrefixedRotationMatrixStampedFbsBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<simple_msgs::RotationMatrixStampedFbs> root) {
  fbb.FinishSizePrefixed(root, RotationMatrixStampedFbsIdentifier());
}

}  // namespace simple_msgs

#endif  // FLATBUFFERS_GENERATED_ROTATIONMATRIXSTAMPED_SIMPLE_MSGS_H_
