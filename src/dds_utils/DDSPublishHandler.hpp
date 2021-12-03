
#ifndef CYCLONE_BRIDGE__SRC__DDS_UTILS__DDSPUBLISHHANDLER_HPP
#define CYCLONE_BRIDGE__SRC__DDS_UTILS__DDSPUBLISHHANDLER_HPP

#include <memory>

#include <dds/dds.h>

namespace cyclone_bridge {
namespace dds {

template <typename Message>
class DDSPublishHandler
{
public:

  using SharedPtr = std::shared_ptr<DDSPublishHandler>;

private:

  dds_return_t return_code;

  const dds_topic_descriptor_t* topic_desc;

  dds_entity_t topic;

  dds_entity_t writer;

  bool ready;

public:

  DDSPublishHandler(
      const dds_entity_t& _participant,
      const dds_topic_descriptor_t* _topic_desc,
      const std::string& _topic_name) :
    topic_desc(_topic_desc)
  {
    ready = false;

    topic = dds_create_topic(
        _participant, _topic_desc, _topic_name.c_str(), NULL, NULL);
    if (topic < 0)
    {
      DDS_FATAL("dds_create_topic: %s\n", dds_strretcode(-topic));
      return;
    }

    dds_qos_t* qos = dds_create_qos();
    dds_qset_reliability(qos, DDS_RELIABILITY_BEST_EFFORT, 0);
    writer = dds_create_writer(_participant, topic, qos, NULL);
    if (writer < 0)
    {
      DDS_FATAL("dds_create_writer: %s\n", dds_strretcode(-writer));
      return;
    }
    dds_delete_qos(qos);

    ready = true;
  }

  ~DDSPublishHandler()
  {}

  bool is_ready()
  {
    return ready;
  }

  bool write(Message* msg)
  {
    return_code = dds_write(writer, msg);
    if (return_code != DDS_RETCODE_OK)
    {
      DDS_FATAL("dds_write failed: %s", dds_strretcode(-return_code));
      return false;
    }
    return true;
  }

};

} // namespace dds
} // namespace cyclone_bridge

#endif // CYCLONE_BRIDGE__SRC__DDS_UTILS__DDSPUBLISHHANDLER_HPP
