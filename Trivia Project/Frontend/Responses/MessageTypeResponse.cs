using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

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
