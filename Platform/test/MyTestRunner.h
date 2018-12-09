#ifndef _H_MyTestRunner
#define _H_MyTestRunner
#pragma once

#include "UMachine.h"


#include "iggy.h"

using namespace igloo;

class CodeliteResultsOutput : public TestResultsOutput
{
public:
	CodeliteResultsOutput(std::ostream& outstream = std::cout) : TestResultsOutput(outstream) {}
	void PrintResult(const TestResults& results) const
	{
		for (TestResults::FailedTestsType::const_iterator it = results.FailedTests().begin(); it != results.FailedTests().end(); it++)
		{
			const FailedTestResult& result = *it;
			output << result.GetContextName() << "::" << result.GetSpecName() << " failed:" << std::endl;
			if(result.HasLineNumber() && result.HasFilename())
			{
				output
						<< result.Filename()
						<< ":" << result.LineNumber()
						<< ":1: error: Assertion failed. "
						<< result.GetErrorMessage() << std::endl;
				//output <<  result.Filename() << ":" << result.LineNumber() << ": Assertion failed." << std::endl << result.GetErrorMessage() << std::endl;
			}
			else
			{
				output << result.GetErrorMessage() << std::endl;
			}
		}
		output << "Test run complete. " << results.NumberOfTestsRun() << " tests run, " << results.NumberOfSucceededTests() << " succeeded, " << results.NumberOfFailedTests() << " failed." << std::endl;
	}
};

inline
int	Runner(int argc, const char* argv[])
{
	int	nResult = 0;
#if defined(_MSC_VER)  &&  0
	VisualStudioResultsOutput	oOutput;
	TestRunner	oRunner(oOutput);
	nResult = oRunner.RunAllTests(argc, argv);
#else
	CodeliteResultsOutput	oOutput;
	TestRunner	oRunner(oOutput);
	nResult = oRunner.RunAllTests(argc, argv);
	//nResult = TestRunner::RunAllTests();
#endif
	return nResult;
}


//	For linux create an environment variable such as:
//
//	TESTLEAKS=valgrind --log-fd=-1
//
//





#endif	// _H_MyTestRunner
