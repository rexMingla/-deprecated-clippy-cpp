/* See the file "LICENSE.md" for the full license governing this code. */
#ifndef PROCESS_H
#define PROCESS_H

class ProcessPrivate;
class QKeySequence;

/**
 * @brief Class for interacting with a process for two tasks: assigning focus and sending key presses.
 *
 *        This is heavily os dependent. An attempt was made to use the Qt private impl os switching though I think
 *        I would have preferred having an interface with an impl for each Os to make readability better.
 *
 *        Also, this extra layer of abstration with the private impl could probably be done away with. At the time I
 *        thought there was a chance that the pimpls would need to share common functions but that has not been the case.
 */
class Process
{
private:
  ProcessPrivate* pimpl_;

public:
  Process();
  ~Process();

  void setAsFocusedWindow();
  void sendKeys(const QKeySequence& keySequence);
};

#endif // PROCESS_H
