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
    internal struct GetPlayersInRoomResponse
    {
        public List<string> players;
    }
}
