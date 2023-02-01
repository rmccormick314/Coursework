import java.util.Random;

public class Contestant {
  int HP = 0;
  int damage = 0;
  String damageType = "";
  String classType = "";

  public void Contestant(){}
  public void Contestant(String classType){
    this.classType = classType;
  }

  public void Attack(){}

  public void setHP(int amount){
    this.HP = amount;
  }

  public int getHP(){
    return this.HP;
  }

  public String getClasstype(){
    return this.classType;
  }

  public String display(){
    String desc = "";
    return desc;
  }

  public boolean isAlive(){
    if (this.HP > 0){
      return true;
    }
    else {
      return false;
    }
  }
  public Contestant setTarget(Contestant[] contestants){
    Contestant target = contestants[random.nextIn(6)]
    if (target.isAlive()){
      return target;
    }
    else {
      target = contestants[random.nextInt(6)];
      return target;
    }
  }
}
