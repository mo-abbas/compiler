#pragma warning disable 0649

using FileHelpers;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CompilerProject
{
    [DelimitedRecord(",")]
    class delimitedFile
    {
        public string Name;
        public string Type;
        public string ScopeId;
        public string constant;
       
    }
}
