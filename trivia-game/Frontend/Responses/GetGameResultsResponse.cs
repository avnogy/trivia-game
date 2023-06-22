using System.Collections.Generic;

namespace Frontend.Responses
{
    public struct PlayerResults
    {
        public string username;
        public int correctAnswerCount;
        public int wrongAnswerCount;
        public float averageAnswerTime;
    }

    public struct GetGameResultsResponse
    {
        public int status;
        public List<PlayerResults> results;
    };
}