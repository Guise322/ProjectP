using System;
using System.Xml;

namespace APIWork
{
    class SpellerAPI
    {
        public string[] XmlYandexAPIWordsVariants(string strData)
        {
            XmlDocument xmlDoc = new XmlDocument();
            try
            {
                string connectStatus = "\r\n Connecting to Yandex.Speller... ";
                Console.Write(connectStatus);

                xmlDoc.Load("https://speller.yandex.net/services/spellservice/checkText?text=" + strData);

                Console.WriteLine("Done");

                XmlNodeList xmlErrorList = xmlDoc.GetElementsByTagName("error");
                // The even numbers of replasingSet elements are words that need to replace, 
                //and the odd numbers are replacing words
                string[] replacingSet = new string[2 * (xmlErrorList.Count)];
                int i = 0;
                int j = 1;
                foreach (XmlNode xmlError in xmlErrorList)
                {
                    XmlNode firstErrorChild = xmlError.FirstChild;
                    replacingSet[i] = firstErrorChild.InnerText;
                    i += 2;
                    XmlNode lastErrorChild = xmlError.LastChild;
                    replacingSet[j] = lastErrorChild.InnerText;
                    j += 2;

                    // The statements below take the position attribute of a not-correct word
                    //XmlAttributeCollection xmlErrorAttributeCollection = xmlError.Attributes;
                    //Console.WriteLine(xmlErrorAttributeCollection[1].InnerText);
                }
                return replacingSet;
            }
            catch (System.Net.WebException)
            {
                Console.WriteLine("No connection!");

                string[] error = new string[2] { "###", "###" };
                return error;
            }
            /*xmlDoc.LoadXml("<?xml version=\"1.0\" encoding=\"utf-8\"?><SpellResult>" +
                "<error code=\"1\" pos=\"0\" row=\"0\" col=\"0\" len=\"8\"><word>Polindos</word>" +
                "<s>Polindoz</s><s>Polidos</s><s>Polindros</s></error>" +
                "<error code =\"1\" pos=\"0\" row=\"0\" col=\"0\" len=\"8\"><word>Polindos</word>" +
                "<s>Polindoz</s><s>Polidos</s><s>Polindros</s></error></SpellResult>");*/
        }
    }
}
