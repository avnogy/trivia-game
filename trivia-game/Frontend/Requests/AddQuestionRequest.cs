using System;
using System.Collections.Generic;

namespace Frontend.Requests
{
    internal struct AddQuestionRequest
    {
        public String question;
        public IList<String> possibleAnswers;
        public String correctAnswer;
    }
}