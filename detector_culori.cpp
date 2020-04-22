#include &lt;LiquidCrystal.h&gt;
//mapare lcd
LiquidCrystal lcd(7, 6, 5, 4, 3, 2);//RS,EN,D4,D5,D6,D7
// clasa de baza
class componenta{
	public:
	int s0;
	int s1;
	int s2;
	int s3;
	int out;
//functie care identifica culoriile principale (R-rosu,G-verde,B-blue)
	void color();
//constructor
	componenta(int a, int b, int c, int d, int e)
		{
			s0=a;
			s1=b;
			s2=c;
			s3=d;
			out=e;
		}
//de clarare clasa prietena
	friend class culori;
};
//setarea pinilor pentru senzor
componenta senzor(8,9,10,11,12);
//clasa prietena
class culori
	{
		public:
		int red;
		int green;
		int blue;
		//constructor
		culori(){
		red = 0;
		green = 0;
		blue = 0;
	}
//functie pentru citirea frecventei
void serPrt()
	{
		Serial.print(&quot;R Intensity:&quot;);
		Serial.print(red, DEC);
		Serial.print(&quot; G Intensity: &quot;);
		Serial.print(green, DEC);
		Serial.print(&quot; B Intensity : &quot;);
		Serial.print(blue, DEC);
	}
};
culori colors;
//initializarea modului in care sunt setati pinii fiecarei componente
//daca sunt de intrare sau de iesire
	void setup()
	{
		Serial.begin(9600);
		lcd.begin(16, 2);
		// pinii pentru senzorul de culoare
		pinMode(senzor.s0, OUTPUT);
		pinMode(senzor.s1, OUTPUT);
		pinMode(senzor.s2, OUTPUT);
		pinMode(senzor.s3, OUTPUT);
		pinMode(senzor.out, INPUT);
		//setarea pinilor s0 si s1
		digitalWrite(senzor.s0, HIGH);
		digitalWrite(senzor.s1, LOW);
//se va obtine o scalare de 20% (a se vedea documentatia)
	}
//codul propriu-zis ce indeplineste functia ceruta
	void loop()
	{
		//afisare pe lcd in partea de sus
		lcd.setCursor(0, 0);
		//printare mesaj de inceput pe lcd
		lcd.print(&quot; Color Detected &quot;);
		//preluarea frecventei culorii
		senzor.color();
		//afisare in consola
		colors.serPrt();
		//endl
		Serial.println();
		// conditii pentru delimitarea culorilor
		if (colors.red &gt;220 &amp;&amp; colors.red &lt; 245 &amp;&amp; colors.green &lt; 10 &amp;&amp;
		colors.blue &lt;10)
		{
			//afisare culoare in consola
			Serial.println(&quot; - (Red Color)&quot;);
			//afisare pe lcd in partea de jos
			lcd.setCursor(0, 1);
			//afisare pe lcd a culorii
			lcd.print(&quot; RED Color &quot;);
			//o intarziere de 500 de unitati de timp
			delay(500);
		}
		else if (colors.red &gt;240 &amp;&amp; colors.blue &lt; 10 &amp;&amp; colors.green &gt; 240)
		{
			Serial.println(&quot; - (Yellow Color)&quot;);
			lcd.setCursor(0, 1);
			lcd.print(&quot; YELLOW Color &quot;);
			delay(500);
		}
		else if (colors.red &lt; 10 &amp;&amp; colors.blue &gt; 240 &amp;&amp; colors.green &lt; 10)
		{
			Serial.println(&quot; - (Blue Color)&quot;);
			lcd.setCursor(0, 1);
			lcd.print(&quot; BLUE Color &quot;) ;
			delay(500);
		}
		else if (colors.red &lt; 10 &amp;&amp; colors.blue &lt; 10 &amp;&amp; colors.green &lt; 10)
		{
			Serial.println(&quot; - (Black Color)&quot;);
			lcd.setCursor(0, 1);
			lcd.print(&quot; BLACK Color &quot;) ;
			delay(500);
		}
		else if (colors.red &gt; 165 &amp;&amp; colors.blue &gt; 240 &amp;&amp; colors.green &lt; 220)
		{
			Serial.println(&quot; - (Green Color)&quot;);
			lcd.setCursor(0, 1);
			lcd.print(&quot; GREEN Color &quot;);
			delay(500);
		}
		else if(colors.red &lt; 170 &amp;&amp; colors.blue &gt; 230 &amp;&amp; colors.green &lt; 10)
		{	
			Serial.println(&quot; - (Purple Color)&quot;);
			lcd.setCursor(0, 1);
			lcd.print(&quot; PURPLE Color &quot;) ;
			delay(500);
		}
		else if(colors.red &gt;240 &amp;&amp; colors.blue &gt;240 &amp;&amp; colors.green &gt;240)
		{
			Serial.println(&quot; - (White Color)&quot;);
			lcd.setCursor(0, 1);
			lcd.print(&quot; WHITE Color &quot;) ;
			delay(500);
		}
		else if(colors.red &gt;240 &amp;&amp; colors.blue &lt; 10 &amp;&amp; colors.green &lt; 60)
		{
			Serial.println(&quot; - (Orange Color)&quot;);
			lcd.setCursor(0, 1);
			lcd.print(&quot; ORANGE Color &quot;) ;
			delay(500);
		}
		else
		{
			Serial.println();
			lcd.setCursor(0, 1);
			lcd.print(&quot; Can&#39;t Identify&quot;);
			delay (500);
		}
}
// functie care identifica culoriile principale (R-rosu,G-verde,B-albastru)
void componenta::color()
{
int frequency;
//setarea piniilor s2 si s3 pentru culoarea rosie
digitalWrite(s2,LOW);
digitalWrite(s3,LOW);
//citirea pulsatiei
frequency = pulseIn(out, LOW);
//maparea frecventei
frequency = map(frequency, 25,70,255,0);
//constrangere valori pana la un maxim de 255
frequency = constrain(frequency,0,255);
	if(frequency &gt;190 &amp;&amp; frequency &lt;210)
		frequency = 0;
	if(frequency &lt;100)
		frequency = 0;
	colors.red=frequency;
	delay(100);
// setarea piniilor s2 si s3 pentru culoarea verde
	digitalWrite(s2,HIGH);
	digitalWrite(s3,HIGH);
	frequency = pulseIn(out, LOW);
	frequency = map(frequency, 30,50,255,0);
	frequency = constrain(frequency,0,255);
	colors.green=frequency;
	delay(100);
//setarea piniilor s2 si s3 pentru culoarea albastra
	digitalWrite(s2,LOW);
	digitalWrite(s3,HIGH);
	frequency = pulseIn(out, LOW);
	if(frequency &lt;14)
	if(frequency &lt;8)
		frequency = 255;
	else
		frequency = 0;
	else if (frequency &lt;17)
		frequency = 255;
	else
		frequency = 0;
	colors.blue=frequency;
	delay(100);
}