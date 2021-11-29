public class McCrann {
  private String name;
  private String family;
  private boolean selected; //boolean for whether that person has already gotten a gift
  private String givingTo; //string for who they're giving to

  public McCrann(String name, String family) {
    this.name = name;
    this.family = family;
    //selected initialized to false
    this.selected = false;
  }

  public String getName() {
    return this.name;
  }

  public String getFamily() {
    return this.family;
  }

  public boolean isSelected() {
    return this.selected;
  }

  public void gotGift() {
    this.selected = true;
  }

  public void GivesTo(McCrann reciever) {
    this.givingTo = reciever.getName();
    reciever.gotGift();
  }

  public String isGivingTo() {
    return this.givingTo;
  }
}
