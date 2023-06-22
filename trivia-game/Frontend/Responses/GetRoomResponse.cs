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
    public struct GetRoomResponse
    {
		public int status;
		public bool hasGameBegun;
		public List<string> players;
		public int questionCount;
		public int answerTimeout;
	}
}
