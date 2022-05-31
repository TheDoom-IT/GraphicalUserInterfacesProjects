import { useContext, useState } from 'react';
import { BASIC_HEADER, API_LOGIN } from '../constans';
import { StatusCodes } from 'http-status-codes';
import { useLocation, useNavigate } from 'react-router-dom';
import { ResponseLogin } from '../routes/response-types';
import { SessionContext, SessionContextType } from '../App';

export type LoginFormState = {
  information?: string
}

function LoginForm() {

  const context: SessionContextType = useContext(SessionContext)
  const [login, setLogin] = useState("")
  const [password, setPassword] = useState("")
  const [generalError, setGeneralError] = useState("")
  const navigate = useNavigate()
  const location = useLocation()
  const state: LoginFormState = location.state as LoginFormState

  const onSubmit = async (event: React.FormEvent<HTMLFormElement>) => {
    event.preventDefault()
    const res = await fetch(API_LOGIN, {
      method: "POST",
      headers: BASIC_HEADER,
      body: JSON.stringify({
        login,
        password
      })
    })

    await handleResponse(res)
  }

  const handleResponse = async (response: Response) => {
    const json: ResponseLogin = await response.json()

    if (response.status === StatusCodes.OK) {
      if (json.access_token && json.user)
        context.logIn(json.access_token)
      navigate("/")
    } else {
      setGeneralError(json.errors?.general || "")
    }
  }

  return (
    <div className='loginForm'>
      <div className='information'>
        {state?.information}
      </div>
      <div className='generalError'>
        {generalError}
      </div>
      <form onSubmit={(e) => onSubmit(e)}>
        <label className="myLabel">
          Login:
          <input className="textInput" id="login" value={login} required onChange={(e) => setLogin(e.currentTarget.value)} />
          <div className='labelError'></div>
        </label>
        <label className="myLabel">
          Password:
          <input className="textInput" value={password} required type="password" onChange={(e) => setPassword(e.currentTarget.value)} />
          <div className='labelError'></div>
        </label>
        <div className='btn-group'>
          <input className="btn" type="submit" value="Sign In" />
        </div>
      </form>
    </div>
  );
}

export default LoginForm;
