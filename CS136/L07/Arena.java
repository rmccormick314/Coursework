import java.util.ArrayList;
import java.util.Random;

class Arena {
  Contestant[] contestants = new Contestant[6];
  public Arena() {


  }

  int addCounter = 0;
  public void add(Contestant contestant) {
    Contestant tempContestant = contestant;
    contestants[addCounter] = tempContestant;
    addCounter += 1;
  }

  public void playRound() {
    for (Contestant contestant : contestants){
      contestant.setTarget(this.contestants);
    }
  }

  public String getDescription() {
    String description = "";
    for (Contestant contestant : this.contestants){
      description += contestant.display();
    }
    return description;
  }

  public Contestant getWinner() {
    int numberAlive = 6;
    Contestant winner = null;
    for (Contestant contestant : this.contestants){
      if (contestant.isAlive() == false){
        numberAlive -= 1;
      }
    }

    for (Contestant contestant : this.contestants){
      if (numberAlive == 1 && contestant.isAlive()){
        winner = contestant;
      }
    }
    return winner;
  }

}
