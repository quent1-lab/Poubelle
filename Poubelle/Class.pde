
class Com {

  Com() {
  }

  void click() {
    if (auto) {
      Port.write(100);
    } else {
      Port.write(101);
    }
  }

  void Read() {
    while (Port.available() > 0) {
      String sb = Port.readStringUntil('\n');

      if ( sb != null) {
        val = float(sb);
        bval = int(val);
        //println(bval);
      }
    }
  }

  void Write() {
    x++; 
    fill(255);

    if ( x >= 3) {
      x = 0;
      Port.write(envoie[nbEnvoie]);
      delay(100);
      Read();
      if (nbEnvoie >= 0 && nbEnvoie <= 5) {
        valeur[nbValeur] = bval;
      }
    }
    nbEnvoie++;
    nbValeur++;
    
    if ( nbEnvoie > 21) {
      nbEnvoie = 0;
    }
    if ( nbValeur > 21) {
      nbValeur = 0;
    }
  }
}
