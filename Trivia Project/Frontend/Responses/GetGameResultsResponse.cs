using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Frontend.Responses
{
	public struct PlayerResults
	{
		public String username;
		public int correctAnswerCount;
		public int wrongAnswerCount;
		public int averageAnswerTime;
	};

	public struct GetGameResultsResponse
	{
		public int status;
		public IList<PlayerResults> results;
	};
}
