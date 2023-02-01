public class WildMage extends comtestant {
  int HP = 0;
  int damage = 0;
  String damageType = "Fire DMG";
  Boolean dead = false;
  Boolean attack = false;
  int target = 0;
  String class = "WildMage";

  Warrior(){}


  int setTargest(Array[Contestant] contestants){
 for (int i = 0; i < Contestant.length; i++){
   if (Contestant[i].getHealth < Contestant[target].getHealth){
   target = i;
   }
 }
  return target;
  }
  setHealth(){
    this.HP = randint(10,60);
  }
  getHealth(){
    return this.HP;
  }
  setDamage(){
  this.damage = randint(0,6);
  }
  Attack(){
    for (int i = 0; i < Contestant.length; i++){
    Contestant target = "";
    contestants[i] = target;
    target.setHealth(target.getHealth - setDamage());
  }
  }
  display(){
    System.out.println("A Wild Mage" + "( " + getHealth() + " )";
  }
}
