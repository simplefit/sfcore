#ifndef __simplefit_testutils__
#define __simplefit_testutils__

double sum(std::vector<double> & args)
{
  double res(0.);
  for (unsigned i = 0; i < args.size(); ++i) {
    res += double(args[i]);
  }
  return res;
}

#endif	// __simplefit_testutils__
