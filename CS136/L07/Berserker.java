import java.util.Random;

//Creates a new class of type 'Contestant' called Berserker
public class Berserker extends Contestant {
  Random random = new Random();
  //Constructs Berserker with 35 HP and Bludgeoning damage
  public void Berserker(){
    Contestant("Berserker");
    this.HP = 35;
    this.damageType = "Bludgeoning";
  }

  //Attacks require a target, an amount of damage, and a damageType
  public void Attack(Contestant target, int damage){
    int targetHP = target.getHP();
    int damageDone = damage;

    //Berserkers and WildMages take regular damage from Berserkers
    if (target.getClasstype() == "Berserker" || target.getClasstype() == "WildMage"){
      target.setHP(targetHP - damageDone);
    }

    //Warriors have a 25% chance to dodge Berserker attacks
    if (target.getClasstype() == "Warrior"){
      int diceRoll = random.nextInt(4);
      if (diceRoll == 4){
        System.out.println(target.display() + " dodged the attack!");
      }
      else {
        target.setHP(targetHP - damageDone);
      }
    }
  }

  public Contestant setTarget(Contestant[] contestants){
    Contestant target = contestants[random.nextInt(6)];
    return target;
  }

  public void setDamage(int amount){
    this.damage = amount;
  }

  public String display(){
    return ("A raging Berserker" + "( " + getHP() + " )");
  }
}
