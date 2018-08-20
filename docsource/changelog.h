/**
 @page changelog Change Log

<p>

<h3>2005-11-13</h3>
<ul>
<li>Collisions are now resolved in a physical manner.  (Concervation of momentum, etc.)
<li>Added configure(const std::string &name) to all subclasses of Entity.
<li>Moved a number of attributes from public to protected.
<li>Added particle effects.  See particle.ini.
<li>Added screen shake.  See sysconfig.ini for parameters.
<li>Gravity is now 1/r^2 instead of 1/r.
<li>Documentation is now compiled into a single .chm file.
</ul>

<h3>2005-11-13</h3>
<ul>
<li>Added configurable shots.
<li>Renamed myParser -> entityConfig
<li>Merged presentWorld and presentOverlay into Entity::present.
<li>Hue shifted the Saw enemy to create distinct player graphics.
<li>Tuned the player controls.
<li>Refactored mouse control logic into MouseControl.
<li>Refactored joystick control logic into JoystickControl.
<li>Added batch files to clean the project and to rebuild the documentation.
<li>Added sysconfig.ini.  Now possible to reconfigure keys and change the video settings.
<li>Updated documentation.
<li>[FIX] ShooterGamelet: Enemies now have the correct texture.
<li>[FIX] ShooterGamelet: Adding and removing player2 more than once no longer causes crash.
</ul>


<h3>2005-11-06</h3>
<ul>
<li>Added mouse and keyboard control to.
<li>Can now load config files with Parser.
</ul>

<h3>2005-10-29</h3>
<ul>
<li>Added collision primitives (circle, plane, composite).
<li>Added debugging lines to PaperWorld.
<li>Improved the documentation.
<li>Added BlackHole entity.
<li>Improved shadow quality.
<li>Integrated mouse code. (broken)
<li>Added an example of text rendering into ShooterGamelet.
<li>[FIX] Enemy::gunAngle initalized.
</ul>

</p>

 */