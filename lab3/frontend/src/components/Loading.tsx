import { ReactComponent as LoadIcon } from '../images/load-icon.svg';

export function Loading() {
    return (
        <div className="loading-icon-div">
            <LoadIcon className='loading-icon' />
        </div>
    )
}