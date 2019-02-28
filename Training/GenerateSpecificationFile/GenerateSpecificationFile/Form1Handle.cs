using System;
using System.IO;
using OfficeOpenXml;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;
using OfficeOpenXml.Style;

namespace GenerateSpecificationFile
{
    class DataInput
    {
        public string specId;
        public string featureSetId;
        public string priority;
        public string resolutionMethod;
        public string testCondition;
        public string testCoverageItemContents;
        public string testCaseId;
        public string testType;
        public string objective;
        public string preCond;
        public string input;
        public string verify;
        public string expectedResult;
        public string component;
        public string observedOutput;
        public string remarks;
    }

    class Form1Handle
    {
        public static readonly string PRIORITY_KEY = "__Priority";
        public static readonly string RESOLUTIONMETHOD_KEY = "__ResolutionMethod";
        public static readonly string TESTCONDITION_KEY = "__TestCondition";
        public static readonly string TESTCOVERAGE_KEY = "__TestCoverage";
        public static readonly string TESTTYPE_KEY = "__TestType";
        public static readonly string OBJECTIVE_KEY = "__Objective";
        public static readonly string PRECOND_KEY = "__PRECOND";
        public static readonly string INPUT_KEY = "__INPUT";
        public static readonly string VERIFY_KEY = "__VERIFY";
        public static readonly string COMPONENT_KEY = "__Component";
        public static readonly string OBSERVEDOUTPUT_KEY = "__ObservedOutput";
        public static readonly string EXPECTEDRESULT_KEY = "__ExpectedResult";
        public static readonly string REMARKS_KEY = "__Remarks";

        public static string cate1 = "";
        public static bool obs = false;
        public static int num = 0;
        public static FileInfo output;

        enum ReadingState
        {
            __Priority = 1,
            __ResolutionMethod,
            __TestCondition,
            __TestCoverage,
            __TestType,
            __Objective,
            __PRECOND,
            __INPUT,
            __VERIFY,
            __Component,
            __ObservedOutput,
            __ExpectedResult,
            __Remarks,
            NONE
        };

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool AllocConsole();

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern bool FreeConsole();

        public static void GenerateXlxsFile(Form1Data dt, Form1 form)
        {
            //Enalbe print log to console window
            if(dt.enable_console) AllocConsole();

            Console.WriteLine("\n\n\n");
            Console.WriteLine("nGenerateXlxsFile start ...");
            Console.WriteLine("inpuFilePath: " + dt.inpuFilePath);
            Console.WriteLine("outputDir: " + dt.outputDir);
            Console.WriteLine("outputName: " + dt.outputName);
            Console.WriteLine("category: " + dt.category);

            if (CheckValidData(dt))
            {
                num = 0;
                cate1 = dt.category;
                string cate2 = "";
                string line;
                bool gotUUT = false;
                string specId = "", featureSetId = "";
                char tab = '\u0009';
                string outputPath = "";
                
                try
                {
                    StreamReader sr = new StreamReader(dt.inpuFilePath);
                    line = sr.ReadLine();
                    while (line != null)
                    {
                        //write the lie to console window
                        Console.WriteLine(line);
                        // Get test unit
                        int uut = line.IndexOf("-- Unit(s) Under Test");
                        if (uut > -1)
                        {
                            cate2 = line.Substring(23);

                            if (dt.auto_generate_outputName)
                            {
                                //create file name from data was read from .tst
                                outputPath = dt.outputDir + "\\" + "Specification_" + cate2 + ".xlsx";
                            }
                            else
                            {
                                //create file name from input of user
                                outputPath = dt.outputDir + "\\" + dt.outputName;
                            }

                            //create new file
                            output = new FileInfo(outputPath);
                            //Read template file and save to output
                            FileInfo specUnitTest = new FileInfo("specUnitTest\\specUnitTest.xlsx");
                            using (ExcelPackage p = new ExcelPackage(specUnitTest))
                                p.SaveAs(output);

                        }



                        if (!gotUUT)
                        {
                            if (!String.IsNullOrEmpty(specId))
                            {
                                initTest(cate1, cate2, specId);
                                gotUUT = true;
                            }
                        }
                        else { }

                        

                        int index = line.IndexOf("-- Subprogram");
                        if (index > -1)
                        {
                            int indexE = line.IndexOf("::");
                            if (indexE > -1)
                            {
                                specId = line.Substring(19, indexE - 19);
                                featureSetId = line.Substring(indexE + 2);
                            }
                            else
                            {
                                specId = "";
                                featureSetId = line.Substring(15);
                            }
                        }

                        index = line.IndexOf("-- Test Case: ");
                        if (index > -1)
                        {
                            ReadingState oldstate = ReadingState.NONE;
                            DataInput data = new DataInput();
                            while (line != "TEST.END" && line != null)
                            {
                                ReadingState state = ReadingState.NONE;

                                int indexS;
                                //get specId
                                data.specId = specId;

                                //get featureSetId
                                data.featureSetId = featureSetId;

                                //get priority
                                index = line.IndexOf("__Priority");
                                if (index > -1)
                                {
                                    indexS = line.IndexOf(": ");
                                    string Priority = line.Substring(index + 12); //line.Substring(indexS + 2);
                                    data.priority = Priority.Replace(tab.ToString(), " ").Replace(";", "\n");
                                    state = ReadingState.__Priority;
                                }

                                //get resolutionMethod
                                index = line.IndexOf("__ResolutionMethod");
                                if (index > -1)
                                {
                                    indexS = line.IndexOf(": ");
                                    string ResolutionMethod = line.Substring(index + 20); //line.Substring(indexS + 2);
                                    data.resolutionMethod = ResolutionMethod.Replace(tab.ToString(), " ").Replace(";", "\n");
                                    state = ReadingState.__ResolutionMethod;
                                }

                                //get testCondition
                                index = line.IndexOf("__TestCondition");
                                if (index > -1)
                                {
                                    indexS = line.IndexOf(": ");
                                    string TestCondition = line.Substring(index + 17); //line.Substring(indexS + 2);
                                    data.testCondition = TestCondition.Replace(tab.ToString(), " ").Replace(";", "\n");
                                    state = ReadingState.__TestCondition;
                                }

                                //get testCoverageItemContents
                                index = line.IndexOf("__TestCoverage");
                                if (index > -1)
                                {
                                    indexS = line.IndexOf(": ");
                                    string TestCoverage = line.Substring(index + 16); //line.Substring(indexS + 2);
                                    data.testCoverageItemContents = TestCoverage.Replace(tab.ToString(), " ").Replace(";", "\n");
                                    state = ReadingState.__TestCoverage;
                                }

                                //get testCaseId
                                index = line.IndexOf("TEST.NAME");
                                if (index > -1)
                                {
                                    string TestCaseId = line.Substring(10);
                                    data.testCaseId = TestCaseId.Replace("(cl)", "");
                                }

                                //get testType
                                index = line.IndexOf("__TestType");
                                if (index > -1)
                                {
                                    indexS = line.IndexOf(": ");
                                    string TestType = line.Substring(index + 12); //line.Substring(indexS + 2);
                                    data.testType = TestType.Replace(tab.ToString(), " ").Replace(";", "\n");
                                    state = ReadingState.__TestType;
                                }

                                //get objective
                                index = line.IndexOf("__Objective");
                                if (index > -1)
                                {
                                    indexS = line.IndexOf(": ");
                                    string Objective = line.Substring(index + 13); //line.Substring(indexS + 2);
                                    data.objective = Objective.Replace(tab.ToString(), " ").Replace(";", "\n");
                                    state = ReadingState.__Objective;
                                }

                                //get preCond
                                index = line.IndexOf("__PRECOND");
                                if (index > -1)
                                {
                                    indexS = line.IndexOf(": ");
                                    string PRECOND = line.Substring(index + 11); //line.Substring(indexS + 2);
                                    data.preCond = PRECOND.Replace(tab.ToString(), " ").Replace(";", "\n");
                                    state = ReadingState.__PRECOND;
                                }

                                //get input
                                index = line.IndexOf("__INPUT");
                                if (index > -1)
                                {
                                    indexS = line.IndexOf(": ");
                                    string INPUT = line.Substring(index + 9); //line.Substring(indexS + 2);
                                    data.input = INPUT.Replace(tab.ToString(), " ").Replace(";", "\n");
                                    state = ReadingState.__INPUT;
                                }

                                //get verify
                                index = line.IndexOf("__VERIFY");
                                if (index > -1)
                                {
                                    indexS = line.IndexOf(": ");
                                    string VERIFY = line.Substring(index + 10); //line.Substring(indexS + 2);
                                    data.verify = VERIFY.Replace(tab.ToString(), " ").Replace(";", "\n");
                                    state = ReadingState.__VERIFY;
                                }

                                //get expectedResult
                                index = line.IndexOf("__ExpectedResult");
                                if (index > -1)
                                {
                                    indexS = line.IndexOf(": ");
                                    string ExpectedResult = line.Substring(index + 18); //line.Substring(indexS + 2);
                                    data.expectedResult = ExpectedResult.Replace(tab.ToString(), " ").Replace(";", "\n");
                                    state = ReadingState.__ExpectedResult;
                                }

                                //get component
                                index = line.IndexOf("__Component");
                                if (index > -1)
                                {
                                    indexS = line.IndexOf(": ");
                                    string Component = line.Substring(index + 13); //line.Substring(indexS + 2);
                                    data.component = Component.Replace(tab.ToString(), " ").Replace(";", "\n");
                                    state = ReadingState.__Component;
                                }

                                //get observedOutput
                                index = line.IndexOf("__ObservedOutput");
                                if (index > -1)
                                {
                                    indexS = line.IndexOf(": ");
                                    string ObservedOutput;
                                    if (obs)
                                        ObservedOutput = line.Substring(index + 18); //line.Substring(indexS + 2);
                                    else
                                        ObservedOutput = "Same as Expected Result";
                                    data.observedOutput = ObservedOutput.Replace(tab.ToString(), " ").Replace(";", "\n");

                                    state = ReadingState.__ObservedOutput;
                                }

                                //get remarks
                                index = line.IndexOf("__Remarks");
                                if (index > -1)
                                {
                                    indexS = line.IndexOf(": ");
                                    string Remarks = line.Substring(index + 11); //line.Substring(indexS + 2);
                                    data.remarks = Remarks.Replace(tab.ToString(), " ").Replace(";", "\n");

                                    state = ReadingState.__Remarks;
                                }

                                //[2019.02.28] the.vu handll reading many lines on each field
                                if (state != ReadingState.NONE)
                                {
                                    oldstate = state;
                                }
                                else if(oldstate != ReadingState.NONE && state == ReadingState.NONE)
                                {
                                    switch(oldstate)
                                    {
                                        case ReadingState.__TestCondition:
                                            if(data.testCondition[data.testCondition.Length -1].Equals('\n') == false)
                                            {
                                                data.testCondition += "\n";
                                            }
                                            data.testCondition += line.ToString().Trim() ;
                                            break;
                                        case ReadingState.__TestCoverage:
                                            if (data.testCoverageItemContents[data.testCoverageItemContents.Length - 1].Equals('\n') == false)
                                            {
                                                data.testCoverageItemContents += "\n";
                                            }
                                            data.testCoverageItemContents += line.ToString().Trim();
                                            break;
                                        case ReadingState.__PRECOND:
                                            if (data.preCond[data.preCond.Length - 1].Equals('\n') == false)
                                            {
                                                data.preCond += "\n";
                                            }
                                            data.preCond += line.ToString().Trim();
                                            break;
                                        case ReadingState.__INPUT:
                                            if (data.input[data.input.Length - 1].Equals('\n') == false)
                                            {
                                                data.input += "\n";
                                            }
                                            data.input += line.ToString().Trim();
                                            break;
                                        case ReadingState.__VERIFY:
                                            if (data.verify[data.verify.Length - 1].Equals('\n') == false)
                                            {
                                                data.verify += "\n";
                                            }
                                            data.verify += line.ToString().Trim();
                                            break;
                                        case ReadingState.__ObservedOutput:
                                            if (data.observedOutput[data.observedOutput.Length - 1].Equals('\n') == false)
                                            {
                                                data.observedOutput += "\n";
                                            }
                                            data.observedOutput += line.ToString().Trim();
                                            break;
                                        case ReadingState.__ExpectedResult:
                                            if (data.expectedResult[data.expectedResult.Length - 1].Equals('\n') == false)
                                            {
                                                data.expectedResult += "\n";
                                            }
                                            data.expectedResult += line.ToString().Trim();
                                            break;
                                        default:
                                            break;
                                    }
                                }

                                line = sr.ReadLine();
                            }
                            inputLine(data);
                        }

                        //Read the next line
                        line = sr.ReadLine();
                    }

                    System.Windows.Forms.MessageBox.Show("SUCCESS !" + " \n\n" + outputPath);

                    if (dt.enable_console)  FreeConsole();

                    if(dt.auto_open_outputDir)
                    {
                        System.Diagnostics.Process.Start("explorer.exe", dt.outputDir);
                    }
                    
                }
                catch (Exception e)
                {
                    Console.WriteLine("Exception: " + e.Message);
                    System.Windows.Forms.MessageBox.Show("FAIL !" + "\n\nException: " + e.Message);

                    if (dt.enable_console) FreeConsole();
                }

            }
        }

        public static void createOutput()
        {
            FileInfo specUnitTest = new FileInfo("specUnitTest\\specUnitTest.xlsx");
            using (ExcelPackage p = new ExcelPackage(specUnitTest))
                p.SaveAs(output);
        }
        public static void initTest(string cate1, string cate2, string UUT)
        {
            using (ExcelPackage p = new ExcelPackage(output))
            {
                ExcelWorksheet ws = p.Workbook.Worksheets[1];
                ws.Name = cate2;
                ws.Cells["B3"].Value = cate1;
                ws.Cells["D3"].Value = cate2;
                ws.Cells["F3"].Value = UUT;
                ws.Cells["B5"].Value = "Verify coverage for class " + UUT;
                p.Save();
            }
        }
        public static void inputLine(DataInput data)
        {
            int row = 10 + num * 3;
            using (ExcelPackage p = new ExcelPackage(output))
            {
                ExcelWorksheet ws = p.Workbook.Worksheets[1];
                ws.Cells["A" + row].Value = data.specId;
                ws.Cells["A" + row + ":A" + (row + 2)].Merge = true;
                ws.Cells["A" + row + ":A" + (row + 2)].Style.Border.BorderAround(ExcelBorderStyle.Dotted);

                ws.Cells["B" + row].Value = data.featureSetId;
                ws.Cells["B" + row + ":B" + (row + 2)].Merge = true;
                ws.Cells["B" + row + ":B" + (row + 2)].Style.Border.BorderAround(ExcelBorderStyle.Dotted);

                ws.Cells["C" + row].Value = data.priority;
                ws.Cells["C" + row + ":C" + (row + 2)].Merge = true;
                ws.Cells["C" + row + ":C" + (row + 2)].Style.Border.BorderAround(ExcelBorderStyle.Dotted);

                ws.Cells["D" + row].Value = data.resolutionMethod;
                ws.Cells["D" + row + ":D" + (row + 2)].Merge = true;
                ws.Cells["D" + row + ":D" + (row + 2)].Style.Border.BorderAround(ExcelBorderStyle.Dotted);

                ws.Cells["E" + row].Value = data.testCondition;
                ws.Cells["E" + row + ":E" + (row + 2)].Merge = true;
                ws.Cells["E" + row + ":E" + (row + 2)].Style.Border.BorderAround(ExcelBorderStyle.Dotted);

                ws.Cells["F" + row].Value = data.testCoverageItemContents;
                ws.Cells["F" + row + ":F" + (row + 2)].Merge = true;
                ws.Cells["F" + row + ":F" + (row + 2)].Style.Border.BorderAround(ExcelBorderStyle.Dotted);

                ws.Cells["G" + row].Value = data.testCaseId;
                ws.Cells["G" + row + ":G" + (row + 2)].Merge = true;
                ws.Cells["G" + row + ":G" + (row + 2)].Style.Border.BorderAround(ExcelBorderStyle.Dotted);

                ws.Cells["H" + row].Value = data.testType;
                ws.Cells["H" + row + ":H" + (row + 2)].Merge = true;
                ws.Cells["H" + row + ":H" + (row + 2)].Style.Border.BorderAround(ExcelBorderStyle.Dotted);

                ws.Cells["I" + row].Value = data.objective;
                ws.Cells["I" + row + ":I" + (row + 2)].Merge = true;
                ws.Cells["I" + row + ":I" + (row + 2)].Style.Border.BorderAround(ExcelBorderStyle.Dotted);

                ws.Cells["J" + row].Value = "PRECOND";
                ws.Cells["J" + (row + 1)].Value = "INPUT";
                ws.Cells["J" + (row + 2)].Value = "VERIFY";
                ws.Cells["J" + row + ":J" + (row + 2)].Style.Border.BorderAround(ExcelBorderStyle.Dotted);

                ws.Cells["K" + row].Value = data.preCond;
                ws.Cells["K" + (row + 1)].Value = data.input;
                ws.Cells["K" + (row + 2)].Value = data.verify;
                ws.Cells["K" + row + ":K" + (row + 2)].Style.Border.BorderAround(ExcelBorderStyle.Dotted);

                ws.Cells["L" + row].Value = data.expectedResult;
                ws.Cells["L" + row + ":L" + (row + 2)].Merge = true;
                ws.Cells["L" + row + ":L" + (row + 2)].Style.Border.BorderAround(ExcelBorderStyle.Dotted);

                ws.Cells["M" + row].Value = data.component;
                ws.Cells["M" + row + ":M" + (row + 2)].Merge = true;
                ws.Cells["M" + row + ":M" + (row + 2)].Style.Border.BorderAround(ExcelBorderStyle.Dotted);

                ws.Cells["N" + row].Value = data.observedOutput;
                ws.Cells["N" + row + ":N" + (row + 2)].Merge = true;
                ws.Cells["N" + row + ":N" + (row + 2)].Style.Border.BorderAround(ExcelBorderStyle.Dotted);

                ws.Cells["O" + row + ":O" + (row + 2)].Merge = true;
                ws.Cells["O" + row + ":O" + (row + 2)].Style.Border.BorderAround(ExcelBorderStyle.Dotted);

                ws.Cells["P" + row].Value = data.remarks;
                ws.Cells["P" + row + ":P" + (row + 2)].Merge = true;
                ws.Cells["P" + row + ":P" + (row + 2)].Style.Border.BorderAround(ExcelBorderStyle.Dotted);

                p.Save();
                num++;
            }
        }

        private static bool CheckValidData(Form1Data data)
        {
            if (String.IsNullOrEmpty(data.inpuFilePath) || !File.Exists(data.inpuFilePath))
            {
                System.Windows.Forms.MessageBox.Show("ERROR:  InputFile is missing or not existed.");
                return false;
            }
            else if (String.IsNullOrEmpty(data.outputDir) || !Directory.Exists(data.outputDir))
            {
                System.Windows.Forms.MessageBox.Show("ERROR:  outputDir is missing or not existed.");
                return false;
            }
            else if (String.IsNullOrEmpty(data.outputName) && data.auto_generate_outputName == false)
            {
                System.Windows.Forms.MessageBox.Show("ERROR: missing outputName.");
                return false;
            }
            else if (String.IsNullOrEmpty(data.category))
            {
                System.Windows.Forms.MessageBox.Show("ERROR: missing category.");
                return false;
            }

            return true;
        }
    }
}
