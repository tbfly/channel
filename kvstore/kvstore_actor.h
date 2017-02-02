/*
 * kvstore_actor.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef KVSTORE_ACTOR_H
#define KVSTORE_ACTOR_H

#include <mutex>
#include "../message.h"

namespace kvstore {
  class KVStoreActor : public msg::Actor {
    public:
      KVStoreActor() {};
      virtual ~KVStoreActor() {};

    public:
      virtual void PreStart();
      virtual void Receive(Message* msg);
      virtual void PostExit();

    private:
      void Pull(const std::vector<uint64_t>& keys, msg::Message* values);

      void Push(const std::vector<uint64_t>& keys,
          const std::vector<uint64_t>& values);

    private:
      msg::MessageHandler pullHandler_;
      msg::MessageHandler saveHandler_;
      std::mutex lock_;

  };
}


#endif /* !KVSTORE_ACTOR_H */