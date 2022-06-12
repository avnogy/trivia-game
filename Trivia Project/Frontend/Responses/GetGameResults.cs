using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using Frontend.Requests;
using Frontend.Responses;

namespace Frontend.Responses
{
    public struct PlayerResults
	{
		public string username;
		public int correctAnswerCount;
		public int wrongAnswerCount;
		public int averageAnswerTime;

	}

	public struct GetGameResultsResponse
	{
		public int status;
		public List<PlayerResults> results;
	};

}
