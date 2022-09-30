import xml.sax

class Portugol( xml.sax.ContentHandler ):
   def __init__(self):
      self.CurrentData = ""   
      self.origin = ""
      self.destination = ""
      self.read = ""

   # Call when an element starts
   def startElement(self, tag, attributes):
      self.CurrentData = tag
         
   # Call when an elements ends
   def endElement(self, tag):
      if self.CurrentData == "from":
         print ("from:", self.origin)
      elif self.CurrentData == "to":
         print ("to:", self.destination)
      elif self.CurrentData == "read":
         print ("read:", self.read)
         print("")
      self.CurrentData = ""

   # Call when a character is read
   def characters(self, content):
      if self.CurrentData == "from":
         self.origin = content
      elif self.CurrentData == "to":
         self.destination = content
      elif self.CurrentData == "read":
         self.read = content
  
if ( __name__ == "__main__"):
   
   # create an XMLReader
   parser = xml.sax.make_parser()
   # turn off namepsaces
   parser.setFeature(xml.sax.handler.feature_namespaces, 0)

   # override the default ContextHandler
   Handler = Portugol()
   parser.setContentHandler( Handler )
   print("TRANSITIONS: \n")
   parser.parse("/home/rodrigo/Documents/Compiladores/Trabalhos/T1/portugol.jff")