var _____WB$wombat$assign$function_____ = function(name) {return (self._wb_wombat && self._wb_wombat.local_init && self._wb_wombat.local_init(name)) || self[name]; };
if (!self.__WB_pmw) { self.__WB_pmw = function(obj) { this.__WB_source = obj; return this; } }
{
  let window = _____WB$wombat$assign$function_____("window");
  let self = _____WB$wombat$assign$function_____("self");
  let document = _____WB$wombat$assign$function_____("document");
  let location = _____WB$wombat$assign$function_____("location");
  let top = _____WB$wombat$assign$function_____("top");
  let parent = _____WB$wombat$assign$function_____("parent");
  let frames = _____WB$wombat$assign$function_____("frames");
  let opener = _____WB$wombat$assign$function_____("opener");

function closePopup() {
    // Get elements
    const popup = document.getElementById('popup');
    const overlay = document.getElementById('overlay');
    
    // Add closing animation
    popup.classList.add('fade-out');
    overlay.classList.add('fade-out');
    
    // Wait for animation to complete before hiding
    setTimeout(() => {
        popup.style.display = 'none';
        overlay.style.display = 'none';
        
        // Remove animation classes for next use
        popup.classList.remove('fade-out');
        overlay.classList.remove('fade-out');
        
        // Reset form and call typeLogin
        resetForm();
        typeLogin();
    }, 300); // Match this duration with your CSS animation time
    
    // Dispatch custom event
    const popupClosedEvent = new Event('popupClosed');
    document.dispatchEvent(popupClosedEvent);
}

// Helper function to reset form if needed
function resetForm() {
    const form = document.querySelector('#popup form');
    if (form) {
        form.reset();
    }
}

}
/*
     FILE ARCHIVED ON 11:49:16 Apr 29, 2025 AND RETRIEVED FROM THE
     INTERNET ARCHIVE ON 05:55:46 May 28, 2025.
     JAVASCRIPT APPENDED BY WAYBACK MACHINE, COPYRIGHT INTERNET ARCHIVE.

     ALL OTHER CONTENT MAY ALSO BE PROTECTED BY COPYRIGHT (17 U.S.C.
     SECTION 108(a)(3)).
*/
/*
playback timings (ms):
  captures_list: 0.445
  exclusion.robots: 0.022
  exclusion.robots.policy: 0.013
  esindex: 0.009
  cdx.remote: 205.076
  LoadShardBlock: 198.58 (3)
  PetaboxLoader3.datanode: 214.58 (5)
  PetaboxLoader3.resolve: 241.296 (4)
  load_resource: 300.577 (2)
*/