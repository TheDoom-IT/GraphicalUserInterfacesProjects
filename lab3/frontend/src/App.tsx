import './App.css';
import { ReactComponent as Logo } from './images/logo.svg'
import { Outlet, useNavigate } from 'react-router-dom';
import { NavBar } from './components/NavBar';
import { createContext, useState } from 'react';
import { isJWTsaved, removeJWT, saveJWT } from './jwt-token';
import { PATH_LOGGED_OUT } from './routes/constants';

export type SessionContextType = {
  isLoggedIn: boolean
  logIn: (jwtToken: string) => void
  logOut: () => void
}

export const SessionContext = createContext<SessionContextType>({ isLoggedIn: false, logIn: (jwtToken: string) => { }, logOut: () => { } })

function App() {
  const [isLoggedIn, setIsLoggedIn] = useState(isJWTsaved())
  const navigate = useNavigate()

  const logOut = () => {
    removeJWT()
    setIsLoggedIn(false)
    navigate(PATH_LOGGED_OUT)
  }

  const logIn = (jwtToken: string) => {
    saveJWT(jwtToken)
    setIsLoggedIn(true)
  }

  return (
    <SessionContext.Provider value={{ isLoggedIn, logIn, logOut }}>
      <div className='container'>
        <Logo className='logo' />
        <NavBar />
        <div className='content'>
          <Outlet />
        </div>
      </div>
    </SessionContext.Provider>
  );
}

export default App;
