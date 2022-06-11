using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Frontend.Responses
{
    internal struct GetQuestionResponse
    {
        public int status;
        public String question;
        public IList<String> possibleAnswers;
        public String correctAnswer;
    }
}
