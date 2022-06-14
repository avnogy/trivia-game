using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Frontend.Requests
{
    internal struct AddQuestionRequest
    {
        public String question;
        public IList<String> possibleAnswers;
        public String correctAnswer;
    }
}
