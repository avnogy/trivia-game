using System;
using System.Collections.Generic;

namespace Frontend.Responses
{
    internal struct GetQuestionResponse
    {
        public int status;
        public String question;
        public IList<String> possibleAnswers;
    }
}