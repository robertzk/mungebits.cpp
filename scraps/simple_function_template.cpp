#include <iostream>
#include <map>
#include <string>
#include <vector>

// template<typename T>
class Mungebit {
protected:
  bool  trained; 
  int   input_length;
  void* input;

public:

  // Functions are responsible for their own serialization and deserialization.
  virtual bool train(const double* data, const size_t &size, const void *train_args) = 0;
  virtual const double* predict(const double* data, const void *predict_args) const = 0;

  Mungebit() : trained(false) { }
  ~Mungebit() { std::free(input); }
};

class DoublerMungebit : public Mungebit {
  bool train(const double* data, const size_t &size, const void *train_args) {
    return true;
  }

  double* predict(const double* data, const void *predict_args) const {
    double* output;
    for (auto i = 0; i < 10; ++i) output[i] = i / 10.0;
    return output;
  }
};

int main(int argc, char** argv) {
  Mungebit *m = new DoublerMungebit();
}


