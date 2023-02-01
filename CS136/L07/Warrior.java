public class Warrior extends comtestant {
  Warrior(){
    setHP()
  }


  int setTargest(Array[Contestant] contestants){
    for (int i = 0; i < Contestant.length; i++){
      if (Contestants[i].getHealth < Contestants[target].getHealth){
        target = i;
      }
    }
    return target;
  }

  Attack(){
    Contestant target = "";
    contestants[target] = target;
    target.setHealth(target.getHealth - setDamage());
  }
  display(){
    System.out.println("A disciplined Warrior" + "( " + getHealth() + " )";
  }
}
