
#ifndef CYCLONE_BRIDGE__SRC__DDS_UTILS__DDSSUBSCRIBEHANDLER_HPP
#define CYCLONE_BRIDGE__SRC__DDS_UTILS__DDSSUBSCRIBEHANDLER_HPP

#include <memory>
#include <vector>

#include <dds/dds.h>

namespace cyclone_bridge {
namespace dds {

template <typename Message, size_t MaxSamplesNum = 1>
class DDSSubscribeHandler
{
public:

  using SharedPtr = std::shared_ptr<DDSSubscribeHandler>;

private:

  dds_return_t return_code;

  const dds_topic_descriptor_t* topic_desc;

  dds_entity_t topic;
  
  dds_entity_t reader;
  
  std::array<std::shared_ptr<Message>, MaxSamplesNum> shared_msgs;

  void* samples[MaxSamplesNum];

  dds_sample_info_t infos[MaxSamplesNum];

  bool ready;

public:

  DDSSubscribeHandler(
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
      DDS_FATAL(
          "dds_create_topic: %s\n", dds_strretcode(-topic));
      return;
    }

    dds_qos_t* qos = dds_create_qos();
    dds_qset_reliability(qos, DDS_RELIABILITY_BEST_EFFORT, 0);
    reader = dds_create_reader(_participant, topic, qos, NULL);
    if (reader < 0)
    {
      DDS_FATAL(
          "dds_create_reader: %s\n", dds_strretcode(-reader));
      return;
    }
    dds_delete_qos(qos);

    for (size_t i = 0; i < shared_msgs.size(); ++i)
    {
      shared_msgs[i] = std::shared_ptr<Message>((Message*)dds_alloc(sizeof(Message)));
      samples[i] = (void*)shared_msgs[i].get();
    }

    ready = true;
  }

  ~DDSSubscribeHandler()
  {}

  bool is_ready()
  {
    return ready;
  }

  std::vector<std::shared_ptr<const Message>> read()
  {
    std::vector<std::shared_ptr<const Message>> msgs;
    if (!is_ready())
      return msgs;

    return_code = dds_take(reader, samples, infos, MaxSamplesNum, MaxSamplesNum);
    if (return_code < 0)
    {
      DDS_FATAL("dds_take: %s\n", dds_strretcode(-return_code));
      msgs.clear();
      return msgs;
    }
    
    if (return_code > 0)
    {
      for (size_t i = 0; i < MaxSamplesNum; ++i)
      {
        if (infos[i].valid_data)
          msgs.push_back(std::shared_ptr<const Message>(shared_msgs[i]));
      }
      return msgs;
    }
    msgs.clear();
    return msgs;
  }

};

} // namespace dds
} // namespace cyclone_bridge


#endif // CYCLONE_BRIDGE__SRC__DDS_UTILS__DDSSUBSCRIBEHANDLER_HPP
