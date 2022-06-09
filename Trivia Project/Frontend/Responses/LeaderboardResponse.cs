using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Frontend.Responses
{
    internal struct LeaderboardResponse
    {
        public int status;   
        public List<string> highScore;
    }
}
