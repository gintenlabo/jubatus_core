// This file is auto-generated from stat.idl
// *** DO NOT EDIT ***

#include <map>
#include <string>
#include <vector>
#include <utility>

#include "../framework.hpp"
#include "stat_server.hpp"
#include "stat_serv.hpp"

namespace jubatus {
namespace server {

class stat_impl_ : public stat<stat_impl_> {
 public:
  explicit stat_impl_(const jubatus::framework::server_argv& a):
    stat<stat_impl_>(a.timeout),
    p_(new jubatus::framework::server_helper<stat_serv>(a, true)) {
  }
  std::string get_config(std::string name) {
    JRLOCK__(p_);
    return get_p()->get_config();
  }
  
  bool push(std::string name, std::string key, double value) {
    JWLOCK__(p_);
    return get_p()->push(key, value);
  }
  
  double sum(std::string name, std::string key) {
    JRLOCK__(p_);
    return get_p()->sum(key);
  }
  
  double stddev(std::string name, std::string key) {
    JRLOCK__(p_);
    return get_p()->stddev(key);
  }
  
  double max(std::string name, std::string key) {
    JRLOCK__(p_);
    return get_p()->max(key);
  }
  
  double min(std::string name, std::string key) {
    JRLOCK__(p_);
    return get_p()->min(key);
  }
  
  double entropy(std::string name, std::string key) {
    JRLOCK__(p_);
    return get_p()->entropy(key);
  }
  
  double moment(std::string name, std::string key, int32_t degree,
       double center) {
    JRLOCK__(p_);
    return get_p()->moment(key, degree, center);
  }
  
  bool clear(std::string name) {
    JWLOCK__(p_);
    return get_p()->clear();
  }
  
  bool save(std::string name, std::string id) {
    JWLOCK__(p_);
    return get_p()->save(id);
  }
  
  bool load(std::string name, std::string id) {
    JWLOCK__(p_);
    return get_p()->load(id);
  }
  
  std::map<std::string, std::map<std::string, std::string> > get_status(
      std::string name) {
    JRLOCK__(p_);
    return p_->get_status();
  }
  int run() { return p_->start(*this); }
  common::cshared_ptr<stat_serv> get_p() { return p_->server(); }

 private:
  common::cshared_ptr<jubatus::framework::server_helper<stat_serv> > p_;
};

}  // namespace server
}  // namespace jubatus

int main(int argc, char* argv[]) {
  return
    jubatus::framework::run_server<jubatus::server::stat_impl_>
      (argc, argv, "stat");
}
