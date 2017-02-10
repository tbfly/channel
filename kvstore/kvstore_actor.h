/*
 * kvstore_actor.h
 * Copyright (C) 2017 zhangyule <zyl2336709@gmail.com>
 *
 * Distributed under terms of the MIT license.
 */

#ifndef KVSTORE_ACTOR_H
#define KVSTORE_ACTOR_H

#include <unordered_map>
#include <mutex>
#include "../net/communicator.h"
#include "./kvstore_base.h"
#include "sparse_hash_kvstore.h"
#include "../message.h"
#include "../actor.h"

namespace kvstore {
  template <typename Key, typename Value, typename Merger>
  class KVStoreActor : public msg::Actor {
    public:
      KVStoreActor(int id) { this->id = id; }
      virtual ~KVStoreActor() {}

    public:
      virtual void PreStart();
      virtual void Receive(MessagePtr msg);
      virtual void PostExit();

    private:
      void Pull(const std::vector<Key>& keys, msg::MessagePtr values);

      void Push(const std::vector<Key>& keys,
          const std::vector<Value>& values);

    private:
      msg::MessageHandler pullHandler_;
      msg::MessageHandler pushHandler_;
      std::mutex lock_;

    private:
      KVStoreBase* store_;
  };

  template <typename Key, typename Value, typename Merger>
    virtual void KVStoreActor::PreStart() {
      network::Communicator::Get()->Register(this);
      store_ = new SparseHashKVStore<Key, Value>();
    }

  template <typename Key, typename Value, typename Merger>
    virtual void KVStoreActor<Key, Value, Merger>::PostExit() {
      delete store_;
    }

  template <typename Key, typename Value, typename Merger>
    void KVStoreActor<Key, Value, Merger>::Pull() {}

  template <typename Key, typename Value, typename Merger>
    void KVStoreActor<Key, Value, Merger>::Push() {}

}


#endif /* !KVSTORE_ACTOR_H */
