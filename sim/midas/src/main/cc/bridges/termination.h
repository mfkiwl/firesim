
#ifndef __TERMINATION_H
#define __TERMINATION_H
// See LICENSE for license details.

#ifdef TERMINATIONBRIDGEMODULE_struct_guard

#include "bridge_driver.h"

// Bridge Driver Instantiation Template
#define INSTANTIATE_TERMINATION(FUNC, IDX)                                     \
  FUNC(new termination_t(this,                                                 \
                         args,                                                 \
                         TERMINATIONBRIDGEMODULE_##IDX##_substruct_create,     \
                         TERMINATIONBRIDGEMODULE_##IDX##_message_count,        \
                         TERMINATIONBRIDGEMODULE_##IDX##_message_type,         \
                         TERMINATIONBRIDGEMODULE_##IDX##_message));

class termination_t : public bridge_driver_t {
public:
  termination_t(simif_t *sim,
                const std::vector<std::string> &args,
                const TERMINATIONBRIDGEMODULE_struct &mmio_addrs,
                unsigned int num_messages,
                unsigned int *is_err,
                const char *const *msgs);
  ~termination_t();
  virtual void init(){};
  virtual void tick();
  virtual void finish(){};
  virtual bool terminate() { return test_done; };
  virtual int exit_code() { return fail; };
  const char *exit_message();
  int cycle_count();

private:
  const TERMINATIONBRIDGEMODULE_struct mmio_addrs;
  bool test_done = false;
  int fail = 0;
  int tick_rate = 10;
  int tick_counter = 0;
  unsigned int num_messages;
  unsigned int *is_err;
  const char *const *msgs;
};
#endif // TerminationBridgeModule_struct_guard
#endif //__TERMINATION_H