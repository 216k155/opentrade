#ifndef ALGOS_TWAP_TWAP_H_
#define ALGOS_TWAP_TWAP_H_

#include "opentrade/algo.h"
#include "opentrade/security.h"

namespace opentrade {

enum Aggression {
  kAggLow,
  kAggMedium,
  kAggHigh,
  kAggHighest,
};

class TWAP : public Algo {
 public:
  std::string OnStart(const ParamMap& params) noexcept override;
  void OnModify(const ParamMap& params) noexcept override;
  void OnStop() noexcept override;
  void OnMarketTrade(const Instrument& inst, const MarketData& md,
                     const MarketData& md0) noexcept override;
  void OnMarketQuote(const Instrument& inst, const MarketData& md,
                     const MarketData& md0) noexcept override;
  void OnConfirmation(const Confirmation& cm) noexcept override;
  const ParamDefs& GetParamDefs() noexcept override;
  void Timer();
  virtual Instrument* Subscribe();
  virtual const MarketData& md() { return inst_->md(); }
  virtual void Place(Contract* c) { Algo::Place(*c, inst_); }

 protected:
  Instrument* inst_ = nullptr;
  SecurityTuple st_;
  double price_ = 0;
  time_t begin_time_ = 0;
  time_t end_time_ = 0;
  double min_size_ = 0;
  double max_pov_ = 0;
  double initial_volume_ = 0;
  Aggression agg_ = kAggLow;
};

}  // namespace opentrade

#endif  // ALGOS_TWAP_TWAP_H_
