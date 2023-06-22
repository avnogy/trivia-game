using System;

namespace Frontend.Responses
{
    internal struct MessageTypeResponse
    {
        public enum Type
        {
            CorrectAnswerResponse,
            GetGameResultsResponse
        }

        public Type type;
        public String message;
    }
}