import java.util.ArrayList;

public class AmplifiersApp
{
   public static void main(String[] args)
   {
      double r1 = 4;
      double r2 = 20;
      ArrayList<Amplifier> amplifiers = new ArrayList<Amplifier>();

      amplifiers.add(new InvertingAmplifier(r1, r2));
      amplifiers.add(new NoninvertingAmplifier(r1, r2));
      amplifiers.add(new VdivAmplifier(r1, r2));
      for (int i = 0; i < amplifiers.size(); i++)
      {
         System.out.println(amplifiers.get(i).getDescription() + "\n"
               + "Gain: " + amplifiers.get(i).getGain());
      }
   }
}
