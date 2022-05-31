import { StatusCodes } from 'http-status-codes';
import { useState } from 'react';
import { useNavigate } from 'react-router-dom';
import { BASIC_HEADER, API_REGISTER } from '../constans';
import { PATH_LOGIN } from '../routes/constants';

type RegisterResponse = {
  id?: number
  login?: string
  email?: string
  errors?: {
    login?: string
    email?: string
    password?: string
    general?: string
  }
}
function RegisterForm() {
  const navigate = useNavigate()
  const handleLoginChange = (event: React.FormEvent<HTMLInputElement>) => {
    setLogin(event.currentTarget.value)
  }
  const handlePasswordChange = (event: React.FormEvent<HTMLInputElement>) => {
    setPassword(event.currentTarget.value)
  }
  const handleEmailChange = (event: React.FormEvent<HTMLInputElement>) => {
    setEmail(event.currentTarget.value)
  }
  const [login, setLogin] = useState("")
  const [password, setPassword] = useState("")
  const [email, setEmail] = useState("")
  const [loginError, setLoginError] = useState("")
  const [passwordError, setPasswordError] = useState("")
  const [emailError, setEmailError] = useState("")
  const [generalError, setGeneralError] = useState("")

  const onSubmit = async (event: React.FormEvent<HTMLFormElement>) => {
    event.preventDefault()
    const res = await fetch(API_REGISTER, {
      method: "POST",
      headers: BASIC_HEADER,
      body: JSON.stringify({
        login,
        email,
        password
      })
    })
    await handleResponse(res)
  }

  const handleResponse = async (res: Response) => {
    if (res.status === StatusCodes.CREATED) {
      navigate(PATH_LOGIN, { state: { information: "Your account was succesfully created. You can now log in." } })
    } else {
      const json: RegisterResponse = await res.json()
      setLoginError(json.errors?.login || "")
      setPasswordError(json.errors?.password || "")
      setEmailError(json.errors?.email || "")
      setGeneralError(json.errors?.general || "")
    }
  }

  return (
    <form onSubmit={(e) => onSubmit(e)}>
      <div className='generalError'>{generalError}</div>
      <label className='myLabel'>
        Login:
        <input className="textInput" value={login} required onChange={(e) => handleLoginChange(e)} />
        <div className='labelError'>{loginError}</div>
      </label>
      <label className='myLabel'>
        Email:
        <input className="textInput" value={email} required onChange={(e) => handleEmailChange(e)} />
        <div className='labelError'>{emailError}</div>
      </label>
      <label className='myLabel'>
        Password:
        <input className="textInput" value={password} required type="password" onChange={(e) => handlePasswordChange(e)} />
        <div className='labelError'>{passwordError}</div>
      </label>
      <div className='btn-group'>
        <input className="btn" type="submit" value="Sign Up" />
      </div>
    </form>
  );
}

export default RegisterForm;
