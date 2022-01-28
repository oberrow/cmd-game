function button(var text, var action,var buttonId, var quirk) {
  if(quirk = 1)
  {
    <form action=action>
            <input id=buttonId type="submit" value=text />
    </form>
    <br>
    <br>
  }
  else {
   <form action=action>
            <input id=buttonId type="submit" value=text />
        </form>
   <br> 
   <br>
  }
}
