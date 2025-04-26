// tDCS সার্কিটের জন্য Arduino কোড
// এই কোডটি tDCS এর জন্য প্রয়োজনীয় কার্যকলাপ সম্পাদন করে
// কারেন্ট নিয়ন্ত্রণ, সুইচ স্টেট, এবং স্টিমুলেশন সময়ের জন্য

// পিন ডিফাইনেশন
const int currentPin = 9;         // পিন যার মাধ্যমে কারেন্ট নিয়ন্ত্রণ হবে
const int switchPin = 2;          // সুইচ পিন (tDCS চালু বা বন্ধ করার জন্য)
const int ledPin = 13;            // LED পিন, যাতে tDCS সক্রিয় বা নিষ্ক্রিয় হওয়ার অবস্থান প্রদর্শিত হয়

// ভ্যারিয়েবল
int switchState = 0;              // সুইচের অবস্থা (চালু/বন্ধ)
unsigned long stimulationTime = 1200000; // 20 মিনিট (স্টিমুলেশন সময়, মিলিসেকেন্ডে)
unsigned long startTime;         // স্টিমুলেশন শুরু সময়
int targetCurrent = 2;            // টার্গেট কারেন্ট (mA), 1-2mA রেঞ্জের মধ্যে

// সিস্টেম সেটআপ ফাংশন
void setup() {
  // সুইচ পিন ইনপুট হিসেবে সেট করা হচ্ছে
  pinMode(switchPin, INPUT);

  // পিনগুলো আউটপুট হিসেবে সেট করা হচ্ছে
  pinMode(currentPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  
  // সিরিয়াল মনিটর শুরু করা হচ্ছে (ডিবাগের জন্য)
  Serial.begin(9600);
  startTime = millis(); // স্টিমুলেশন শুরু হওয়া সময়
  Serial.println("tDCS সিস্টেম চালু...");
}

// মূল লুপ
void loop() {
  // সুইচের অবস্থা চেক করা হচ্ছে
  switchState = digitalRead(switchPin);
  
  if (switchState == HIGH) { // সুইচ চালু থাকলে
    // tDCS চালু করুন (এখানে আপনার ট্রানজিস্টর বা ট্রান্সফর্মার ব্যবহার করা হতে পারে)
    digitalWrite(currentPin, HIGH); // কারেন্ট চালু
    digitalWrite(ledPin, HIGH);     // LED অন (tDCS সক্রিয় হওয়ার সংকেত)

    // সিরিয়াল মনিটরেও tDCS চালু হওয়ার বার্তা প্রেরণ করা হচ্ছে
    Serial.println("tDCS চালু");
    
    // স্টিমুলেশন সময় চেক করুন (যতক্ষণ না স্টিমুলেশন সময় শেষ হয়)
    if (millis() - startTime >= stimulationTime) {
      // স্টিমুলেশন সময় শেষ হলে tDCS বন্ধ করুন
      digitalWrite(currentPin, LOW);  // কারেন্ট বন্ধ
      digitalWrite(ledPin, LOW);      // LED বন্ধ (tDCS নিষ্ক্রিয়)

      // সিরিয়াল মনিটরেও বার্তা পাঠানো হচ্ছে
      Serial.println("tDCS বন্ধ");
      
      // সময় রিসেট করা হচ্ছে
      startTime = millis();
    }
  } else { // সুইচ বন্ধ থাকলে
    // যদি সুইচ বন্ধ থাকে, তাহলে tDCS বন্ধ করুন
    digitalWrite(currentPin, LOW);  // কারেন্ট বন্ধ
    digitalWrite(ledPin, LOW);      // LED বন্ধ
    
    // সিরিয়াল মনিটরেও বার্তা পাঠানো হচ্ছে
    Serial.println("tDCS বন্ধ");
  }
}