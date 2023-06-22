using System.Collections.Generic;

namespace Frontend.Responses
{
    internal struct LeaderboardResponse
    {
        public int status;
        public List<string> highScore;
    }
}