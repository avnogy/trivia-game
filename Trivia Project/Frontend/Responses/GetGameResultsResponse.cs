using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Frontend.Responses
{
	internal struct PlayerResults
	{
		String username;
		int correctAnswerCount;
		int wrongAnswerCount;
		int averageAnswerTime;
	};

	internal struct GetGameResultsResponse
	{
		int status;
		IList<PlayerResults> results;
	};
}
