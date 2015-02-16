#ifndef __simplefit_testutils__
#define __simplefit_testutils__

double sum(std::vector<double> & args)
{
  double res(0.);
  for (auto el : args) {
    res += el;
  }
  return res;
}

#endif	// __simplefit_testutils__
