/// \file sheratan/process/posix/daemonizer.hpp
/// \brief POSIX daemonizer interface.
/// \ingroup sheratan_process_posix
/// \author Marek Balint \c (mareq[A]balint[D]eu)


#ifndef HG_SHERATAN_PROCESS_POSIX_DAEMONIZER_HPP
#define HG_SHERATAN_PROCESS_POSIX_DAEMONIZER_HPP


#include <memory>

#include <boost/noncopyable.hpp>

#include "sheratan/utility/explicit_value.hpp"
#include "sheratan/process/posix/types.hpp"
#include "sheratan/process/posix/process_id.hpp"
#include "sheratan/process/posix/daemon_ctl.hpp"


namespace sheratan {

namespace process_impl {

namespace posix {


class daemonization_resources;


/// \brief Daemonizer POSIX implementation.
/// \ingroup sheratan_process_posix
/// \nosubgrouping
class daemonizer : private boost::noncopyable 
{
  public:

    /// \brief PID file path value traits.
    /// \ingroup sheratan_process_posix
    /// \nosubgrouping
    struct pid_file_value_traits
    {
      /// \brief Value type.
      typedef std::string value_type;

      /// \brief Value tag.
      /// \ingroup sheratan_process_posix
      /// \nosubgrouping
      struct tag
      {
        /// \brief Value tag values.
        typedef enum
        {
          PID_FILE  ///< PID file.
        } value_type;
      };

      /// \brief Default value.
      /// \return Default value.
      /// \par Abrahams exception guarantee:
      /// strong
      static pid_file_value_traits::value_type default_value();
    };

    /// \brief PID file path type definition.
    typedef sheratan::utility::explicit_value<daemonizer::pid_file_value_traits, daemonizer::pid_file_value_traits::tag::PID_FILE> pid_file_type;

    /// \brief PID file mode value traits.
    /// \ingroup sheratan_process_posix
    /// \nosubgrouping
    struct pid_file_mode_value_traits
    {
      /// \brief Value type.
      typedef file_mode_type value_type;

      /// \brief Value tag.
      /// \ingroup sheratan_process_posix
      /// \nosubgrouping
      struct tag
      {
        /// \brief Value tag values.
        typedef enum
        {
          PID_FILE_MODE  ///< PID file mode.
        } value_type;
      };

      /// \brief Default value.
      /// \return Default value.
      /// \par Abrahams exception guarantee:
      /// strong
      static pid_file_mode_value_traits::value_type default_value();
    };

    /// \brief PID file mode type definition.
    typedef sheratan::utility::explicit_value<daemonizer::pid_file_mode_value_traits, daemonizer::pid_file_mode_value_traits::tag::PID_FILE_MODE> pid_file_mode_type;

    /// \brief Working directory path value traits.
    /// \ingroup sheratan_process_posix
    /// \nosubgrouping
    struct working_dir_value_traits
    {
      /// \brief Value type.
      typedef std::string value_type;

      /// \brief Value tag.
      /// \ingroup sheratan_process_posix
      /// \nosubgrouping
      struct tag
      {
        /// \brief Value tag values.
        typedef enum
        {
          WORKING_DIR  ///< Working directory.
        } value_type;
      };

      /// \brief Default value.
      /// \return Default value.
      /// \par Abrahams exception guarantee:
      /// strong
      static working_dir_value_traits::value_type default_value();
    };

    /// \brief Working directory type definition.
    typedef sheratan::utility::explicit_value<daemonizer::working_dir_value_traits, daemonizer::working_dir_value_traits::tag::WORKING_DIR> working_dir_type;

    /// \brief Standard I/O streams redirection path value traits.
    /// \ingroup sheratan_process_posix
    /// \nosubgrouping
    struct stdstreams_redirect_value_traits
    {
      /// \brief Value type.
      typedef std::string value_type;

      /// \brief Value tag.
      /// \ingroup sheratan_process_posix
      /// \nosubgrouping
      struct tag
      {
        /// \brief Value tag values.
        typedef enum
        {
          STDIN_REDIRECT,   ///< Standard input redirection path.
          STDOUT_REDIRECT,  ///< Standard output redirection path.
          STDERR_REDIRECT   ///< Standard error redirection path.
        } value_type;
      };

      /// \brief Default value.
      /// \return Default value.
      /// \par Abrahams exception guarantee:
      /// strong
      static stdstreams_redirect_value_traits::value_type default_value();
    };

    /// \brief Standard input redirection path type definition.
    typedef sheratan::utility::explicit_value<daemonizer::stdstreams_redirect_value_traits, daemonizer::stdstreams_redirect_value_traits::tag::STDIN_REDIRECT> stdin_redirect_type;

    /// \brief Standard output redirection path type definition.
    typedef sheratan::utility::explicit_value<daemonizer::stdstreams_redirect_value_traits, daemonizer::stdstreams_redirect_value_traits::tag::STDOUT_REDIRECT> stdout_redirect_type;

    /// \brief Standard error redirection path type definition.
    typedef sheratan::utility::explicit_value<daemonizer::stdstreams_redirect_value_traits, daemonizer::stdstreams_redirect_value_traits::tag::STDERR_REDIRECT> stderr_redirect_type;

    /// \brief Reset signal dispositions to default flag value traits.
    /// \ingroup sheratan_process_posix
    /// \nosubgrouping
    struct reset_signals_flag_value_traits
    {
      /// \brief Value type.
      typedef bool value_type;

      /// \brief Value tag.
      /// \ingroup sheratan_process_posix
      /// \nosubgrouping
      struct tag
      {
        /// \brief Value tag values.
        typedef enum
        {
          RESET_SIGNALS_FLAG ///< Reset signal dispositions to default flag.
        } value_type;
      };

      /// \brief Default value.
      /// \return Default value.
      /// \par Abrahams exception guarantee:
      /// strong
      static reset_signals_flag_value_traits::value_type default_value();
    };

    /// \brief Reset signal dispositions to default flag type definition.
    typedef sheratan::utility::explicit_value<daemonizer::reset_signals_flag_value_traits, daemonizer::reset_signals_flag_value_traits::tag::RESET_SIGNALS_FLAG> reset_signals_flag_type;

  public:

    /// \brief Default constructor.
    /// \par Abrahams exception guarantee:
    /// strong
    daemonizer();

    /// \brief Constructor.
    /// \param dc Daemon controller.
    /// \param pid_file Path to the daemon's PID file. No PID file will be
    /// used, if ommited.
    /// \param pid_file_mode Mode to be used for creation of PID file.
    /// \param working_dir Path to the daemon's working directory. Working
    /// directory will not be changed, if ommited.
    /// \param stdin_redirect Standard input redirection path. Standard input
    /// will not be redirected, if ommited.
    /// \param stdout_redirect Standard output redirection path. Standard output
    /// will not be redirected, if ommited.
    /// \param stderr_redirect Standard error redirection path. Standard error
    /// will not be redirected, if ommited.
    /// \param reset_signals_flag Reset all signal handlers to default values
    /// in the daemon process.
    /// \par Abrahams exception guarantee:
    /// strong
    explicit daemonizer(
      const daemon_ctl &dc,
      const daemonizer::pid_file_type &pid_file = daemonizer::pid_file_type(),
      const daemonizer::pid_file_mode_type &pid_file_mode = daemonizer::pid_file_mode_type(),
      const daemonizer::working_dir_type &working_dir = daemonizer::working_dir_type(),
      const daemonizer::stdin_redirect_type &stdin_redirect = daemonizer::stdin_redirect_type(),
      const daemonizer::stdout_redirect_type &stdout_redirect = daemonizer::stdout_redirect_type(),
      const daemonizer::stderr_redirect_type &stderr_redirect = daemonizer::stderr_redirect_type(),
      const daemonizer::reset_signals_flag_type &reset_signals_flag = daemonizer::reset_signals_flag_type()
    );

  public:

    /// \brief Get daemon controller.
    /// \return Daemon controller.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \pre Object must not be created by default constructor.
    const daemon_ctl & get_daemon_ctl() const;

    /// \brief Get daemon controller.
    /// \return Daemon controller.
    /// \par Abrahams exception guarantee:
    /// no-throw
    /// \pre Object must not be created by default constructor.
    daemon_ctl & get_daemon_ctl();

  public:

    /// \brief Daemonize.
    /// \param daemon_process Daemon process object.
    /// \par Abrahams exception guarantee:
    /// strong
    /// \pre Object must not be created by default constructor.
    /// \note Call to this method will spawn a new process and return
    /// in its calling process. However, it will never return in daemon
    /// process.
    void daemonize(daemon &daemon_process);

  private:

    /// \brief Daemonizer resources.
    std::auto_ptr<daemonization_resources> resources_;
};


} // namespace posix

} // namespace process_impl

} // namespace sheratan


#endif // HG_SHERATAN_PROCESS_POSIX_DAEMONIZER_HPP


// vim: set ts=2 sw=2 et:


