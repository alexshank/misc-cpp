#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>

using namespace curlpp::options;

#include <string>
#include <iostream>
std::string url;

int main(int, char **)
{
	try
	{
		// That's all that is needed to do cleanup of used resources
		curlpp::Cleanup myCleanup;

		// Our request to be sent.
		curlpp::Easy myRequest;

		// Get and set the URL.
		std::cout << "Enter URL to get HTML from:" << std::endl;
		std::cin >> url;
		myRequest.setOpt<Url>(url);

		// Send request and get a result.
		// By default the result goes to standard output.
		myRequest.perform();
	}
	catch(curlpp::RuntimeError & e)
	{
		std::cout << e.what() << std::endl;
	}
	catch(curlpp::LogicError & e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}
