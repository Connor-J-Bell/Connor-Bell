import java.util.Random;

public class McCrannChristmasSwap {

  public static void main(String args[]){
    //Set up a list for the adults
    McCrann[] AdultList = setupAdults();
    McCrann[] cousinList = setupCousins();

    getPairs(AdultList);
    getPairs(cousinList);

    printPairList(AdultList, "Adult Gift Swap");
    printPairList(cousinList, "Cousin Gift Swap");

  }

  public static void printPairList(McCrann[] list, String title){
    System.out.println(title);
    for(int i = 0; i < list.length; i++){
      System.out.println(list[i].getName() + "\t is giving to:\t" + list[i].isGivingTo());
    }
  }

  public static void getPairs(McCrann[] list) {
    //Randomizer object
    Random random = new Random();
    //Iterate through the list
    for(int i = 0; i < list.length; i++) {
      int rand;
      do { //generate random numbers until a valid McCrann is found
        rand = random.nextInt(list.length);
      } while(list[i].getFamily().equals(list[rand].getFamily()) || list[rand].isSelected());
      //while the families are the same, or they've already been selected
      list[i].GivesTo(list[rand]);
    }
  }

  public static McCrann[] setupAdults() {
    McCrann grandpa = new McCrann("Donald", "McCrann Sr.");
    McCrann grandma = new McCrann("Susan", "McCrann Sr.");
    McCrann martha = new McCrann("Martha", "Calandrelli");
    McCrann chris = new McCrann("Chris", "Calandrelli");
    McCrann lauren = new McCrann("Lauren", "Bell");
    McCrann james = new McCrann("James", "Bell");
    McCrann carol = new McCrann("Carol", "Coyle");
    McCrann carson = new McCrann("Carson", "Coyle");
    McCrann beth = new McCrann("Beth", "Taylor");
    McCrann adam = new McCrann("Adam", "Taylor");
    McCrann katie = new McCrann("Katie", "McBig");
    McCrann bo = new McCrann("Bo", "McBig");
    McCrann dj = new McCrann("DJ", "McCrann Jr.");
    McCrann mary = new McCrann("Mary", "McCrann Jr.");
    McCrann maggie = new McCrann("Maggie", "Pugh");
    McCrann jon = new McCrann("Jon", "Pugh");
    McCrann mo = new McCrann("Maureen", "Sturtevant");
    McCrann kevin = new McCrann("Kevin", "Sturtevant");

    McCrann[] adultList = {grandpa, grandma, martha, chris, lauren, james, carol, carson, beth, adam, katie, bo, dj, mary, maggie, jon, mo, kevin};
    return adultList;
}

  public static McCrann[] setupCousins() {
  McCrann jack = new McCrann("Jack", "Calandrelli");
  McCrann paul = new McCrann("Paul", "Calandrelli");
  McCrann connor = new McCrann("Connor", "Bell");
  McCrann ryan = new McCrann("Ryan", "Bell");
  McCrann lucy = new McCrann("Lucy", "Taylor");
  McCrann grady = new McCrann("Grady", "Taylor");
  McCrann paige = new McCrann("Paige", "Taylor");
  McCrann zach = new McCrann("Zach", "Taylor");
  McCrann dana = new McCrann("Dana", "McBig");
  McCrann tess = new McCrann("Tess", "McBig");
  McCrann patrick = new McCrann("Patrick", "McCrann Jr.");
  McCrann max = new McCrann("Max", "McCrann Jr.");
  McCrann winnie = new McCrann("Winslow", "McCrann Jr.");
  McCrann cullen = new McCrann("Cullen", "Pugh");
  McCrann ally = new McCrann("Allison", "Pugh");
  McCrann sam = new McCrann("Sam", "Sturtevant");
  McCrann grace = new McCrann("Grace", "Sturtevant");

  McCrann[] cousinList = {jack, paul, connor, ryan, lucy, grady, paige, zach, dana, tess, patrick, max, winnie, cullen, ally, sam, grace};
  return cousinList;
}

}
