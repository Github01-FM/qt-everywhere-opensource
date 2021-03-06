// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SCHEDULER_BASE_WORK_QUEUE_SETS_H_
#define COMPONENTS_SCHEDULER_BASE_WORK_QUEUE_SETS_H_

#include <stddef.h>

#include <map>
#include <vector>

#include "base/macros.h"
#include "base/trace_event/trace_event_argument.h"
#include "components/scheduler/base/task_queue_impl.h"
#include "components/scheduler/scheduler_export.h"

namespace scheduler {
namespace internal {
class TaskQueueImpl;

class SCHEDULER_EXPORT WorkQueueSets {
 public:
  explicit WorkQueueSets(size_t num_sets);
  ~WorkQueueSets();

  // O(log num queues)
  void RemoveQueue(WorkQueue* work_queue);

  // O(log num queues)
  void AssignQueueToSet(WorkQueue* queue, size_t set_index);

  // O(log num queues)
  void OnPushQueue(WorkQueue* work_queue);

  // If empty it's O(1) amortized, otherwise it's O(log num queues)
  void OnPopQueue(WorkQueue* work_queue);

  // O(1)
  bool GetOldestQueueInSet(size_t set_index, WorkQueue** out_work_queue) const;

  // O(1)
  bool IsSetEmpty(size_t set_index) const;

 private:
  typedef std::map<EnqueueOrder, WorkQueue*> EnqueueOrderToWorkQueueMap;
  std::vector<EnqueueOrderToWorkQueueMap> enqueue_order_to_work_queue_maps_;

  DISALLOW_COPY_AND_ASSIGN(WorkQueueSets);
};

}  // namespace internal
}  // namespace scheduler

#endif  // COMPONENTS_SCHEDULER_BASE_WORK_QUEUE_SETS_H_
