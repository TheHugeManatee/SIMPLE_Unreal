// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_HEADER_SIMPLE_MSGS_H_
#define FLATBUFFERS_GENERATED_HEADER_SIMPLE_MSGS_H_

#include "flatbuffers/flatbuffers.h"

namespace simple_msgs {

struct HeaderFbs;

struct HeaderFbs FLATBUFFERS_FINAL_CLASS : private flatbuffers::Table {
  enum {
    VT_SEQUENCE_NUMBER = 4,
    VT_FRAME_ID = 6,
    VT_TIMESTAMP = 8
  };
  int32_t sequence_number() const {
    return GetField<int32_t>(VT_SEQUENCE_NUMBER, 0);
  }
  const flatbuffers::String *frame_id() const {
    return GetPointer<const flatbuffers::String *>(VT_FRAME_ID);
  }
  int64_t timestamp() const {
    return GetField<int64_t>(VT_TIMESTAMP, 0);
  }
  bool Verify(flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int32_t>(verifier, VT_SEQUENCE_NUMBER) &&
           VerifyOffset(verifier, VT_FRAME_ID) &&
           verifier.Verify(frame_id()) &&
           VerifyField<int64_t>(verifier, VT_TIMESTAMP) &&
           verifier.EndTable();
  }
};

struct HeaderFbsBuilder {
  flatbuffers::FlatBufferBuilder &fbb_;
  flatbuffers::uoffset_t start_;
  void add_sequence_number(int32_t sequence_number) {
    fbb_.AddElement<int32_t>(HeaderFbs::VT_SEQUENCE_NUMBER, sequence_number, 0);
  }
  void add_frame_id(flatbuffers::Offset<flatbuffers::String> frame_id) {
    fbb_.AddOffset(HeaderFbs::VT_FRAME_ID, frame_id);
  }
  void add_timestamp(int64_t timestamp) {
    fbb_.AddElement<int64_t>(HeaderFbs::VT_TIMESTAMP, timestamp, 0);
  }
  explicit HeaderFbsBuilder(flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  HeaderFbsBuilder &operator=(const HeaderFbsBuilder &);
  flatbuffers::Offset<HeaderFbs> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = flatbuffers::Offset<HeaderFbs>(end);
    return o;
  }
};

inline flatbuffers::Offset<HeaderFbs> CreateHeaderFbs(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t sequence_number = 0,
    flatbuffers::Offset<flatbuffers::String> frame_id = 0,
    int64_t timestamp = 0) {
  HeaderFbsBuilder builder_(_fbb);
  builder_.add_timestamp(timestamp);
  builder_.add_frame_id(frame_id);
  builder_.add_sequence_number(sequence_number);
  return builder_.Finish();
}

inline flatbuffers::Offset<HeaderFbs> CreateHeaderFbsDirect(
    flatbuffers::FlatBufferBuilder &_fbb,
    int32_t sequence_number = 0,
    const char *frame_id = nullptr,
    int64_t timestamp = 0) {
  return simple_msgs::CreateHeaderFbs(
      _fbb,
      sequence_number,
      frame_id ? _fbb.CreateString(frame_id) : 0,
      timestamp);
}

inline const simple_msgs::HeaderFbs *GetHeaderFbs(const void *buf) {
  return flatbuffers::GetRoot<simple_msgs::HeaderFbs>(buf);
}

inline const simple_msgs::HeaderFbs *GetSizePrefixedHeaderFbs(const void *buf) {
  return flatbuffers::GetSizePrefixedRoot<simple_msgs::HeaderFbs>(buf);
}

inline const char *HeaderFbsIdentifier() {
  return "HEAD";
}

inline bool HeaderFbsBufferHasIdentifier(const void *buf) {
  return flatbuffers::BufferHasIdentifier(
      buf, HeaderFbsIdentifier());
}

inline bool VerifyHeaderFbsBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<simple_msgs::HeaderFbs>(HeaderFbsIdentifier());
}

inline bool VerifySizePrefixedHeaderFbsBuffer(
    flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<simple_msgs::HeaderFbs>(HeaderFbsIdentifier());
}

inline void FinishHeaderFbsBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<simple_msgs::HeaderFbs> root) {
  fbb.Finish(root, HeaderFbsIdentifier());
}

inline void FinishSizePrefixedHeaderFbsBuffer(
    flatbuffers::FlatBufferBuilder &fbb,
    flatbuffers::Offset<simple_msgs::HeaderFbs> root) {
  fbb.FinishSizePrefixed(root, HeaderFbsIdentifier());
}

}  // namespace simple_msgs

#endif  // FLATBUFFERS_GENERATED_HEADER_SIMPLE_MSGS_H_
