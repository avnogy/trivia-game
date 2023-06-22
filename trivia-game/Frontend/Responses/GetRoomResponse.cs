using System.Collections.Generic;

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